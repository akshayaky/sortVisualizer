#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <random>
#include "fontData.h"
//#include "Source.cpp"

enum Sort {
    Selection = 0, Bubble, Insertion
};

class SortState
{

public:
    static bool isAscendingOrder;
    static Sort currentSort;
    static int currentIndex;
    static int currentIndex2;
    static int waitTime;
    static int speed;

    SortState()
    {
        speed = 100;
    }

    static bool GetOrder() { return isAscendingOrder; }
    static Sort GetSort() { return currentSort; }
    static int GetWaitTime() { return waitTime; }
    static void ChangeOrder(bool isAscendingOrder_)
    {
        isAscendingOrder = isAscendingOrder_;
    }

    static void ChangeSorting(Sort sortingAlgo)
    {
        currentSort = sortingAlgo;
    }

    static int speedCalc()
    {
        speed = 100 - (waitTime - 100);
        return speed;
    }

    static void ChangeWaitTime(int addTime)
    {
        if ((addTime > 0 && waitTime < 150) || (addTime < 0 && waitTime > 10))
        {
            waitTime += addTime;
            speedCalc();
        }
        printf("%d\n", waitTime);

    }
};
bool SortState::isAscendingOrder = true;
Sort SortState::currentSort = Sort::Selection;
int SortState::currentIndex = 0;
int SortState::currentIndex2 = 0;
int SortState::waitTime = 100;
int SortState::speed;
void SetText(sf::Text& text, sf::Font& font, sf::RenderWindow& window, 
    std::string str, int size, sf::Vector2f& textPosition, sf::Color color = sf::Color::Red)
{
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString(str);

    // set the character size
    text.setCharacterSize(size); // in pixels, not points!

    // set the color
    text.setFillColor(color);

    // set the text style
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(sf::Vector2f(textPosition));
}

int Render(std::vector <sf::RectangleShape>& vect_rect, std::vector<int>& vect, sf::RenderWindow& window, bool final, bool isAscendingOrder = true)
{
    bool isPaused = false;
    SortState s;

    sf::Font font;
    if (!font.loadFromMemory(&Yagora_ttf, Yagora_ttf_len))
    {
        std::cout << "File not found";
        return -1;
    }
    std::string str;
    

    sf::Text headingText;
    sf::Vector2f textPosition = sf::Vector2f(200, 10);
    SetText(headingText, font, window, "Sort Visualize", 24, textPosition);

    if (s.GetSort() == Sort::Bubble)
        str = "Bubble Sort";
    else if (s.GetSort() == Sort::Selection)
        str = "Selection Sort";
    else if (s.GetSort() == Sort::Insertion)
        str = "Insertion Sort";
    
    sf::Text currentSortText;
    textPosition = sf::Vector2f(window.getSize().x/2 + 50, window.getSize().y - 100);
    SetText(currentSortText, font, window, str, 20, textPosition, sf::Color::Blue);

    if (s.GetOrder() == true)
        str = "Ascending Order";
    else
        str = "Descending Order";

    sf::Text currentOrderText;
    textPosition = sf::Vector2f(50, window.getSize().y - 100);
    SetText(currentOrderText, font, window, str, 20, textPosition, sf::Color::Blue);

    str = "[1] Selection Sort    [Left Arrow] Ascending Order       [R] Randomize\n"      
          "[2] Bubble Sort         [Right Arrow]  Descending Order\n"
          "[3] Insertion Sort      [Space & K] Pause & Unpause";
    sf::Text InstructionText;
    textPosition = sf::Vector2f(50, window.getSize().y - 50);
    SetText(InstructionText, font, window, str, 15, textPosition, sf::Color::Cyan);

    str = "Speed :" + std::to_string(s.speedCalc()) + "%";
    sf::Text speedText;
    textPosition = sf::Vector2f((window.getSize().x / 4) * 3, window.getSize().y/2);
    SetText(speedText, font, window, str, 15, textPosition, sf::Color::Blue);
    

    
    


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //close window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                return -1;
            }
            //unpause sorting
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                isPaused = false;
            }
            //pause sorting
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                isPaused = true;
            }
            //sort in ascending order
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                
                s.ChangeOrder(true);
                currentSortText.setString("Ascending Order");
                window.draw(currentOrderText);
                window.display();
                return 2;
            }
            //sort in descending order
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                s.ChangeOrder(false);
                currentSortText.setString("Descending Order");
                window.draw(currentOrderText);
                window.display();
                return -2;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {

                s.ChangeSorting(Sort::Selection);
                currentSortText.setString("Selection Sort");
                //std::cout << "Selection sort\n";
                window.draw(currentSortText);
                window.display();
                return 100;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) )
            {
                s.ChangeSorting(Sort::Bubble);
                //std::cout << "Bubble sort\n";
                currentSortText.setString("Bubble Sort");
                window.draw(currentSortText);
                window.display();
                return 200;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                s.ChangeSorting(Sort::Insertion);
                
                currentSortText.setString("Insertion Sort");
                window.draw(currentSortText);
                window.display();
                return 300;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {

                s.ChangeWaitTime(-10);
                speedText.setString("Speed :" + std::to_string(s.speed) + "%");
                
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {

                s.ChangeWaitTime(10);
                speedText.setString("Speed :" + std::to_string(s.speed) + "%");

            }

            

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {

                auto rng = std::default_random_engine{};
                std::shuffle(std::begin(vect), std::end(vect), rng);
                isPaused = false;
                //std::cout << "Hello\n";
                //return -1;

            }
        }
        if (isPaused)
        {
            /*std::cout << "this" << "\n";
            window.close();*/
            continue;

        }
        window.clear();
        
        //printf(" this   ");
        for (int i = 0; i < vect_rect.size(); i++)
        {

            vect_rect[i].setPosition(sf::Vector2f(window.getSize().x/4 + 3 * (i + 1), window.getSize().y/2 + (100 - vect[i] * 2.5f)));
            vect_rect[i].setSize(sf::Vector2f(2, vect[i] * 2.5f));

            if(i == s.currentIndex)
                vect_rect[i].setFillColor(sf::Color::Red);
            else if (i == s.currentIndex2)
                vect_rect[i].setFillColor(sf::Color::Blue);

            /*else if(i < s.currentIndex)
                vect_rect[i].setFillColor(sf::Color::Blue);*/
            else
                vect_rect[i].setFillColor(sf::Color::White);

            window.draw(vect_rect[i]);
        }
        window.draw(headingText);
        window.draw(currentSortText);
        window.draw(currentOrderText);
        window.draw(InstructionText);
        window.draw(speedText);
        window.display();
        //printf(" this2\n");
        if (!final)
            return 0;
    }
        
}


void selection_sort(std::vector<int>& vect, std::vector <sf::RectangleShape>& vect_rect, sf::RenderWindow& window)
{
    SortState s;
    int target = vect[0], index = 0, code;
    for (int i = 0; i < vect.size() - 1;i++)
    {
        s.currentIndex = i;
        for (int j = i + 1; j < vect.size();j++)
        {
            if ((s.GetOrder() && vect[j] < target) || (!s.GetOrder() && vect[j] > target))
            {
                target = vect[j];
                index = j;
                s.currentIndex2 = j;
            }
        }
        vect[index] = vect[i];
        vect[i] = target;
        target = vect[i + 1];
        index = i + 1;

        int code = Render(vect_rect, vect, window, i == vect.size() - 2);
        if (code == -1 || code > 2)
            break;
        else if (code == 2 || code == -2)
        {
            i = -1;
        }
        
        
        sf::sleep(sf::milliseconds(s.GetWaitTime()));
        
    }
}

void bubble_sort(std::vector<int>& vect, std::vector <sf::RectangleShape>& vect_rect, sf::RenderWindow& window, bool isAscendingOrder = true)
{
    SortState s;
    int temp, code;
   
    int i, j;
    for (i = 0; i < vect.size() - 1; i++)
    {
        s.currentIndex = i;
        for (j = 0; j < vect.size() - i - 1; j++)
        {
            if ((s.GetOrder() && vect[j] > vect[j + 1]) || (!s.GetOrder() && vect[j] < vect[j + 1]))
            {
                s.currentIndex2 = j;
                temp = vect[j];
                vect[j] = vect[j + 1];
                vect[j + 1] = temp;
            }
        }

        code = Render(vect_rect, vect, window, i == vect.size() - 2);
        
        if (code == -1 || code > 2)
            break;
        else if (code == 2 || code == -2)
        {
            //isAscendingOrder = true;
            i = -1;
        }
        
        sf::sleep(sf::milliseconds(s.GetWaitTime()));
        
    }
}

void insertion_sort(std::vector<int>& vect, std::vector <sf::RectangleShape>& vect_rect, sf::RenderWindow& window)
{
    SortState s;
    int key, index = 0, code;
    int i, j;
    for (i = 1; i < vect.size(); i++)
    {
        key = vect[i];
        j = i - 1;
        s.currentIndex = i;
        while((s.GetOrder() && (j >= 0 && vect[j] > key)) || (!s.GetOrder() && (j >= 0 && vect[j] < key)))
        {
            vect[j + 1] = vect[j];
            j -= 1;
            s.currentIndex2 = j;
        }
        vect[j + 1] = key;
        int code = Render(vect_rect, vect, window, i == vect.size() - 1);
        
        if (code == -1 || code > 2)
            break;
        else if (code == 2 || code == -2)
        {
            i = 0;
        }
        

        sf::sleep(sf::milliseconds(s.GetWaitTime()));
    }
}

int main()
{
    int choice;
    

    std::vector<int> vect;
    int Min = 10;
    int Max = 110;

    for (int i = 10; i < 110; i++)
    {
        vect.push_back(std::rand() % (Max + 1 - Min) + Min);
        //vect.push_back(i);
    }


    

    std::vector <sf::RectangleShape> vect_rect;
    sf::RectangleShape rect;
    int x_position = 20;
    for (int i = 0; i < vect.size(); i++)
    {
        vect_rect.push_back(rect);
        vect_rect[i].setPosition(sf::Vector2f(20 * (i + 1), 100 + (100 - vect[i])));
        vect_rect[i].setSize(sf::Vector2f(10, vect[i]));
    }

    SortState s;
    sf::RenderWindow window(sf::VideoMode(800, 500), "Sort Visualization", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    //window.


    do
    {
        //std::cout << "1. Selection Sort\n2. Bubble Sort\n7. Exit\n";
        //std::cin >> choice;
        choice = 10;
        
        
        switch (s.GetSort())
        {
        case Sort::Selection:
            selection_sort(vect, vect_rect, window);
            break;
        case Sort::Bubble:
            bubble_sort(vect, vect_rect, window);
            break;
        case Sort::Insertion:
            insertion_sort(vect, vect_rect, window);
            break;
        case 7:
            std::cout << "Exiting....";
            return 0;
            break;
        default:
            std::cout << "Invalid choice\n";
        }
        /*for (int i = 0; i < vect.size(); i++)
        {
            std::cout << vect[i] << "\n";
        }*/

    } while (choice != 7);
    
    return 0;
}

//int main()
//{
//    Controls ctrls;
//    ctrls._state =new SelectionSort();
//
//}
