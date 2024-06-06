#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

// Represents a single document
class Document {
public:
    int id;
    string content;

    Document(int id, const string& content) : id(id), content(content) {}
};

// Indexes documents by keywords
class Indexer {
private:
    unordered_map<string, vector<int>> index;

    // Helper function to split a string into words
    vector<std::string> split(const string& str, char delimiter) {
        vector<string> tokens;
        :string token;
        istringstream tokenStream(str);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    void addDocument(const Document& doc) {
        vector<string> words = split(doc.content, ' ');
        for (const string& word : words) {
            index[word].push_back(doc.id);
        }
    }

    vector<int> search(const string& keyword) {
        if (index.find(keyword) != index.end()) {
            return index[keyword];
        }
        return {};
    }
};

// Manages the search engine
class SearchEngine {
private:
    vector<Document> documents;
    Indexer indexer;

public:
    void addDocument(const string& content) {
        int id = documents.size();
        Document doc(id, content);
        documents.push_back(doc);
        indexer.addDocument(doc);
    }

    void search(const string& keyword) {
        vector<int> results = indexer.search(keyword);
        if (results.empty()) {
            cout << "No documents found containing the keyword: " << keyword << endl;
        } else {
            cout << "Documents containing the keyword '" << keyword << "':" << endl;
            for (int id : results) {
                cout << "Document " << id << ": " << documents[id].content << endl;
            }
        }
    }
};

int main() {
    SearchEngine searchEngine;
    searchEngine.addDocument("This is a sample document about C++ programming.");
    searchEngine.addDocument("Another document that mentions programming and C++.");
    searchEngine.addDocument("A third document about data structures in C++.");

    cout << "Search results for 'programming':" << endl;
    searchEngine.search("programming");

    cout << "\nSearch results for 'C++':" << endl;
    searchEngine.search("C++");

    cout << "\nSearch results for 'data':" << endl;
    searchEngine.search("data");

    return 0;
}
