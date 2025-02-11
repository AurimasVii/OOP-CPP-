#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <assert.h>

using namespace std;
class Uzduotis {
    private:
        static int count;
        static int nextId;
        int id = 0;
        string name;
        int dateCreated;
    public:
        int dateDue;
        string status;
        bool done;
        int commentQuant = 0;
        vector<string> comments;
        //1 konstruktorius
        Uzduotis(string name, time_t dateCreated, time_t dateDue, string status, bool done) {
            this->id = nextId++;
            count++;
            this->name = name;
            this->dateCreated = dateCreated;
            this->dateDue = dateDue;
            this->status = status;
            this->done = done;
        }
        Uzduotis(string name, string status) {
            this->id = nextId++;
            count++;
            this->name = name;
            this->status = status;

            this->dateCreated = time(0);
            this->dateDue = time(0);
            this->done = false;
        }
        ~Uzduotis() {
            for(auto &comment : comments) {
                comment.clear();
            }
            vector<string>().swap(comments);
            count--;
            
        }

        string getName() {
            return name;
        }

        int getDateCreated() {
            return dateCreated;
        }
        void setDateDue(time_t due) {
            if (due < dateCreated) {
                throw invalid_argument("dateDue cannot be earlier than dateCreated");
            }
            dateDue = due;
        }
        int getDateDue() {
            return dateDue;
        }
       
        void setStatus(string status) {
            this->status = status;
        }
        string getStatus() {
            return status;
        }

        void setDone(bool done) {
            this->done = done;
        }
        bool getDone() {
            return done;   
        }

        void addComment(string comment) {
            comments.push_back(comment);
        }
        void deleteComment(int index) {
            if (index < 0 || index >= comments.size()) {
                throw invalid_argument("Index out of bounds");
            }
            comments.erase(comments.begin() + index);
        }
        int getCommentQuont() {
            return comments.size();
        }

        string getId() {
            return to_string(id);
        }
        time_t getTimeLeft() {
            return dateDue - dateCreated;
        }

        string getDiagnostics() {
            stringstream ss;
            ss << "ID: " << id << endl;
            ss << "Name: " << name << endl;
            ss << "Date Created: " << dateCreated << endl;
            ss << "Date Due: " << dateDue << endl;
            ss << "Time left: " << getTimeLeft() << " seconds" << endl;
            ss << "Status: " << status << endl;
            ss << "Done: " << done << endl;
            for (const auto& comment : comments) {
                ss << comment << "\n";
            }
            ss << '\n';
            return ss.str();
        }
        static int getCount() { return count; }
};

int Uzduotis::count = 0;
int Uzduotis::nextId = 1;
int main() {
    Uzduotis* task;
    time_t createdDate = time(0); // Capture current time
    time_t dueDate = createdDate + 100;
    string status = "In Progress";
    bool done = false;
    string name = "Task1";

    task = new Uzduotis(name, createdDate, dueDate, status, done);
    //geteriai
    assert(task->getName() == name);
    assert(task->getDateCreated() == createdDate);
    assert(task->getDateDue() == dueDate);
    assert(task->getTimeLeft() == dueDate - createdDate);
    assert(task->getStatus() == status);
    assert(task->getDone() == done);
    //seteriai
    task->setDateDue(time(0) + 1000);
    task->setStatus("Done");
    task->setDone(true);
    assert(task->getDateDue() != dueDate);
    assert(task->getStatus() != status);
    assert(task->getDone() != done);

    //numeracija ir count
    assert(task->getId() == "1");
    assert(task->getCount() == 1);

    for(int i = 1; i <= 10; ++i) {
        task = new Uzduotis("Task" + to_string(i), "In Progress");
    }
    assert(task->getId() == "11");
    assert(task->getCount() == 11);
    delete task;
    assert(task->getCount() == 10);
    task = new Uzduotis("Task11", "In Progress");
    assert(task->getId() == "12");

    string comment = "Comment1";
    task->addComment(comment);
    assert(task->comments[0] == comment);
    assert(task->getCommentQuont() == 1);
    task->deleteComment(0);
    assert(task->getCommentQuont() == 0);

    cout << "All assert checks passed successfully!" << endl;
    return 0;
};