#include <map>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#define MAXLEN 200
using namespace std;

struct Type{
    bool isString;
    size_t bytes;

    Type(bool isString, size_t bytes){
        this->isString = isString;
        this->bytes = bytes;
    }
};

class Table{
public:
    dropColumn(string name);
    addColumn(Type type,string name);
    insertValues(vector<string> _nameOfColumns, vector<string> value, size_t activeKey);
    updateValues(size_t key, vector<string> nameOfColumns, vector<string> values);
    deleteValues(size_t key);
    printTheTable();
    /*Table(string nameOfTable);
    ~Table();*/

private:
    //string nameOfTable;
    map< size_t,vector<string> > values;
    vector<Type> typesOfColumns;
    vector<string> nameOfColumns;
};

/*Table::Table(string nameOfTable){
    this->nameOfTable = nameOfTable;
    values = new map();
    typesOfColumns = new vector();
    nameOfColumns = new vector();
}

Table::~Table(){
    delete values;
    delete typesOfColumns;
    delete nameOfColumns;
}*/

Table::dropColumn(string name){
    int i;
    for(i = 0; i < nameOfColumns.size(); ++i)
        if(!nameOfColumns[i].compare(name)) break;
    nameOfColumns.erase(nameOfColumns.begin() + i);
    typesOfColumns.erase(typesOfColumns.begin() + i);
    for(auto j = values.begin(); j != values.end(); ++j)
        (j -> second).erase((j -> second).begin() + i);
}

Table::addColumn(Type type,string name){
    //cout << type.isString << name << endl;
    typesOfColumns.push_back(type);
    nameOfColumns.push_back(name);

    for(auto j = values.begin(); j != values.end(); ++j)
        (j -> second).push_back("");
}


Table::insertValues(vector<string> _nameOfColumns, vector<string> value, size_t activeKey){

    if(values.find(activeKey) != values.end()){
        values[activeKey].clear();
    }
    else{
        vector<string> tmp;
        for(int i = 0; i < _nameOfColumns.size(); ++i)
            tmp.push_back("");
        values.insert(make_pair(activeKey, tmp));
    }
    for(auto i = nameOfColumns.begin(); i != nameOfColumns.end(); ++i){
        (values[activeKey]).push_back("");
        for(auto j = _nameOfColumns.begin(); j < _nameOfColumns.end(); ++j){
            if(*i == *j){
                values[activeKey][i - nameOfColumns.begin()] = value[j - _nameOfColumns.begin()];
                //cout << value[j - _nameOfColumns.begin()] << endl;
            }

        }
    }
}

Table::updateValues(size_t activeKey, vector<string> _nameOfColumns, vector<string> value){
    for(auto i = nameOfColumns.begin(); i != nameOfColumns.end(); ++i){
        //(values[activeKey]).push_back("");
        for(auto j = _nameOfColumns.begin(); j != _nameOfColumns.end(); ++j){
            if(*i == *j){
                values[activeKey][i - nameOfColumns.begin()] = value[j - nameOfColumns.begin()];
            }
        }
    }
}

Table::deleteValues(size_t key){
    for(auto i = values.begin(); i != values.end(); ++i)
        if( i -> first == key ){
            (i -> second).clear();
            values.erase(i);
            break;
        }
}

Table::printTheTable(){
    for(auto i = nameOfColumns.begin(); i != nameOfColumns.end(); ++i){
        printf("%s ",(*i).c_str());
    }
    cout << endl;
    for (auto i = values.begin(); i != values.end(); ++i){
        cout << i->first << " ";
        for(auto j = (i->second).begin(); j != (i->second).end(); ++j)
            printf("%s ",j -> c_str());
        cout << endl;
   }
}

printThePossibilities(){
    cout << "\nPress a button";
    cout << "\n1 - Create new data base";
    cout << "\n2 - Add the elements";
    cout << "\n3 - Show full data base";
    cout << "\n4 - Update data";
    cout << "\n5 - Drop column";
    cout << "\n0 - Exit\n";
}

bool intOrString(char* word){
    if(!strcmp(word, "string")) return true;
    else return false;
}
size_t sizeReturner(char* word){
    if(!strcmp(word, "string")) return sizeof(char)*MAXLEN;
    else if(!strcmp(word, "integer"))return sizeof(int);
    else if(!strcmp(word, "double"))return sizeof(double);
}



main(){
    vector<string> nameOfColumns;
    vector<string> value;
    vector<Type> nameOfTypes;
    string name;
    Table table;
    int activeKey;
    ifstream file;
    char* part;
    int m = 1;

    while(m){
        printThePossibilities();
        cin >> m;
        switch(m){
            case 1:
                file.open("file.txt");
                if(!file.is_open())
                    cout << "This file can not to be opened!\n";
                else{
                    char buf[MAXLEN];
                    file.getline(buf,MAXLEN);
                    char *parts = strtok(buf," ");
                    while(parts != NULL){
                            string vmediator(parts);
                            Type tmediator(intOrString(parts),sizeReturner(parts));
                            nameOfTypes.push_back(tmediator);
                            parts = strtok(NULL," ");
                    }
                    file.getline(buf,MAXLEN);
                    char buf1[MAXLEN];
                    strcpy(buf1,buf);
                    parts = strtok(buf," ");
                    while(parts != NULL){
                            string cmediator(parts);
                            nameOfColumns.push_back(cmediator);
                            parts = strtok(NULL," ");
                    }
                    strcpy(buf,buf1);
                    nameOfColumns.erase(nameOfColumns.begin());
                    nameOfTypes.erase(nameOfTypes.begin());
                    for(int i = 0; i < nameOfTypes.size(); ++i)
                            table.addColumn(nameOfTypes[i],nameOfColumns[i]);
                    while(!file.eof()){
                        file.getline(buf,MAXLEN);
                        vector< string > vbuf;
                        parts = strtok(buf," ");
                        while(parts != NULL){
                            string mediator(parts);
                            vbuf.push_back(mediator);
                            parts = strtok(NULL," ");
                        }
                        activeKey = atoi(vbuf[0].c_str());
                        vbuf.erase(vbuf.begin());
                        /*struct Type type(false,sizeof(int));
                        nameOfTypes.push_back(type);
                        string str("lol");
                        nameOfColumns.push_back(str);
                        activeKey = 1;
                        vector<string> vbuf;
                        vbuf.push_back(str);*/
                        table.insertValues(nameOfColumns, vbuf, activeKey);
                        vbuf.clear();
                    }
                }
                //table.printTheTable();
                file.close();
            break;
            case 2:
            break;
            case 3:
                table.printTheTable();
            break;
            case 4:
                nameOfColumns.clear();
                value.clear();
                cout << "Key: ";
                int key;
                cin >> key;
                cout << "Names of columns: ";
                char tmp[MAXLEN];
                cin >> tmp;
                part = strtok(tmp," ");
                while(part != NULL){
                    name.assign(part);
                    nameOfColumns.push_back(name);
                    part = strtok(NULL," ");
                }
                cout << "Values: ";
                cin >> tmp;
                part = strtok(tmp," ");
                while(part != NULL){
                    name.assign(part);
                    value.push_back(name);
                    part = strtok(NULL," ");
                }
                table.updateValues(key,nameOfColumns,value);
            break;
            case 5:
                cout << "Name of column: ";
                cin >> name;
                table.dropColumn(name);
            break;
            case 0:
                return 0;
            }
        }

}

