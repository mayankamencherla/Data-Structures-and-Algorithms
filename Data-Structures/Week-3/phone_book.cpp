#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

struct contact{
	string name;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

void delete_contact(vector<contact> &contacts, int number){
	contacts[number].name = "";
}

void add_contact(vector<contact> &contacts, int number, string name){
	contacts[number].name = name;
}

string find_contact(vector<contact> &contacts, int number){
	if(contacts[number].name == "") return "not found";
	return contacts[number].name;
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<contact> contacts(pow(10,7)); // Query.name, number(only for add) and type
	// contacts(num) should have name
	for (size_t i = 0; i < queries.size(); ++i){
		if (queries[i].type == "add"){
			add_contact(contacts,queries[i].number,queries[i].name);
		}
		
		if(queries[i].type == "del"){
			delete_contact(contacts,queries[i].number);
		}
		
		if(queries[i].type == "find"){
			result.push_back(find_contact(contacts,queries[i].number));
		}
	}
    return result;
} 

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
