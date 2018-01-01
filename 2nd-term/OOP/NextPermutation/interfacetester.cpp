#include "interfacetester.h"

#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>

InterfaceTester::InterfaceTester( int Number, int Range ) {
    commandNumber = Number;
    commandRange = Range;
    createCommands();   // генерируем команды
    clock_t vectorTime = Testing( Vector, false );
    std::cout << "Vector is tested. Time : " << vectorTime << std::endl;
    clock_t treapTime = Testing( Treap, true );
    std::cout << "Treap is tested. Time : " << treapTime << std::endl;
    bool flag = ( vectorAns.size() == treapAns.size() );    // сравниваем количество ответов там и там
    if( !flag )
        std::cout << "- Answers have different size. - " << std::endl;
    int k = 0;
    // если их поровну - сравниваем овтеты
    if( flag )
        for( int i = 0; i < vectorAns.size(); ++i ) {
            flag = ( vectorAns[i] == treapAns[i] );
            if( !flag ) {
                ++k;
            }
        }
    // выводим результат тестирования
    if( flag )
        std::cout << "+ Answers are the same. Tested succesfuly. + " << std::endl;
    else
        std::cout << "- Answers are different. Tested unsuccesfuly. - . Number of wrong answers " << k << std::endl;
}

InterfaceTester::~InterfaceTester() {}

void InterfaceTester::createCommands () {
    std::srand( clock() );
    // первая команда - push
    int count = std::rand() % commandRange;
    Commands.push_back( std::make_pair( testInterface( 1 ), std::make_pair( 0, count ) ) );
    int elementsNumber = 1;
    // создаем остальные команды
    for( int i = 1; i < commandNumber; ++i ) {
        testInterface command = testInterface( rand() % 4 );
        int index1 = rand() % elementsNumber;   // первый элемент - индекс
        // второй - элемент, если push или assign, индекс - если sum или nextPerm
        if( command == 1 || command == 2 ) {
            count = std::rand() % commandRange;
        } else {
            count = std::rand() % elementsNumber;
            // индексы - первый не больше второго
            if( command == 3 ) {
                if( count == elementsNumber - 1 )
                    count = 0;
                if( index1 == elementsNumber - 1)
                    index1 = 0;
            }
            if( count < index1 )
                std::swap( index1, count );
        }
        Commands.push_back( std::make_pair( command, std::make_pair( index1, count ) ) );
        // если команда - push - кол-во элементов + 1
        if ( command == 1 )
            ++elementsNumber;
    }
    std::cout << "Tests are ready" << std::endl;
}

// тестирование
clock_t InterfaceTester::Testing( AbstractArray* arr, bool is_treap ) {
    clock_t time = clock(); // засекаем время
    for( int i = 0; i < commandNumber; ++i ) {
        int ans = 0;
        switch ( Commands[i].first )
        {
        case 0 :
            ans = arr->Sum( Commands[i].second.first, Commands[i].second.second );
            treapAns.push_back(ans);    // добавляем результат в ответы
            break;
        case 1 :
            arr->Push( Commands[i].second.first, Commands[i].second.second );
            break;
        case 2 :
            arr->Assign( Commands[i].second.first, Commands[i].second.second );
            break;
        case 3:
            arr->NextPermutation( Commands[i].second.first, Commands[i].second.second );
            break;
        }
    }
    clock_t result = clock() - time;    //считаем время
    return result;
}
