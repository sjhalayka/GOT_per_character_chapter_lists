// C++ source code to convert book chapter lists
// into per-character chapter lists


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;


class chapter
{
public:
    string name;
    string character_name;
};

class book
{
public:
    string name;
    vector<chapter> chapters;
};

class book_chapter
{
public:
    size_t book_id;
    size_t chapter_id;
};



void load_book(const char *book_title, vector<book> &books);
void build_char_chap_map(vector<book> &books, map<string, vector<book_chapter> > &characters);

int main(void)
{
    vector<book> books;
    map<string, vector<book_chapter> > characters;

    // Read in book chapter lists
    load_book("1_a_game_of_thrones.txt", books);
    load_book("2_a_clash_of_kings.txt", books);
    load_book("3_a_storm_of_swords.txt", books);
    load_book("4_a_feast_for_crows.txt", books);
    load_book("5_a_dance_with_dragons.txt", books);

    // Build the per-character chapter lists
    build_char_chap_map(books, characters);
    
    // Print out per-character chapter lists
    for(map<string, vector<book_chapter> >::const_iterator ci = characters.begin(); ci != characters.end(); ci++)
    {
        cout << ci->first << " : ";

        string last_title = "";

        for(size_t i = 0; i < ci->second.size(); i++)
        {
            if(books[ci->second[i].book_id].name != last_title)
            {
                cout << books[ci->second[i].book_id].name << " ";
                last_title = books[ci->second[i].book_id].name;
            }

            cout << books[ci->second[i].book_id].chapters[ci->second[i].chapter_id].name;

            if(i == ci->second.size() - 1)
                cout << '.' << endl;
            else
                cout << ", ";
        }

        cout << endl;
    }

    return 0;
}


void load_book(const char *book_title, vector<book> &books)
{
    ifstream in(book_title);

    if(in.fail())
    {
        cout << "Error: Could not open file " << book_title << endl;
        return;
    }

    book b;
    getline(in, b.name);

    string ts;
    while(getline(in, ts))
    {
        chapter ch;

        if("" == ts)
            continue;

        bool found_colon = false;
        size_t found_colon_index = 0;

        for(size_t i = 0; i < ts.size(); i++)
        {
            if(':' == ts[i])
            {
                found_colon_index = i;
                found_colon = true;
                break;
            }
        }

        if(false == found_colon)
        {
            ch.name = ts;
        }
        else
        {
            ch.name = ts.substr(0, found_colon_index);

            if(found_colon_index < ts.size() - 1)
                ch.character_name = ts.substr(found_colon_index + 1, ts.size() - found_colon_index  - 1);
        }

        b.chapters.push_back(ch);
    }

    books.push_back(b);
}


void build_char_chap_map(vector<book> &books, map<string, vector<book_chapter> > &characters)
{
    for(size_t i = 0; i < books.size(); i++)
    {
        for(size_t j = 0; j < books[i].chapters.size(); j++)
        {
            if("" != books[i].chapters[j].character_name)
            {
                book_chapter bc;
                bc.book_id = i;
                bc.chapter_id = j;

                characters[books[i].chapters[j].character_name].push_back(bc);
            }
        }
    }
}
