#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include <assert.h>

using namespace std;
class Task {
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

        Task(string name, time_t dateCreated, time_t dateDue, string status, bool done) {
            this->id = nextId++;
            count++;
            this->name = name;
            this->dateCreated = dateCreated;
            this->dateDue = dateDue;
            this->status = status;
            this->done = done;
        }
        Task(string name, string status) {
            this->id = nextId++;
            count++;
            this->name = name;
            this->status = status;

            this->dateCreated = time(0);
            this->dateDue = time(0);
            this->done = false;
        }
        ~Task() {
            comments.clear();
            count--;
        }

        
        void setDateDue(time_t due) {
            if (due < dateCreated) {
                throw invalid_argument("dateDue cannot be earlier than dateCreated");
            }
            dateDue = due;
        }
        void setStatus(string status) {
            this->status = status;
        }
        void setDone(bool done) {
            this->done = done;
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


        string getName() {
            return name;
        }
        int getDateCreated() {
            return dateCreated;
        }
        int getDateDue() {
            return dateDue;
        }
        string getStatus() {
            return status;
        }
        bool getDone() {
            return done;   
        }
        int getCommentQuont() {
            return comments.size();
        }
        int getId() {
            return id;
        }
        static int getCount() {
            return count; 
        }

        string getDiagnostics() {
            stringstream ss;
            ss << "ID: " << id << endl;
            ss << "Name: " << name << endl;
            ss << "Date Created: " << dateCreated << endl;
            ss << "Date Due: " << dateDue << endl;
            ss << "Status: " << status << endl;
            ss << "Done: " << done << endl;
            for (const auto& comment : comments) {
                ss << comment << "\n";
            }
            ss << '\n';
            return ss.str();
        }
        
};

int Task::count = 0;
int Task::nextId = 1;
int main() {
    Task* task;
    time_t createdDate = time(0); 
    time_t dueDate = createdDate + 100;
    string status = "In Progress";
    bool done = false;
    string name = "Task1";

    task = new Task(name, createdDate, dueDate, status, done);

    assert(task->getName() == name);
    assert(task->getDateCreated() == createdDate);
    assert(task->getDateDue() == dueDate);
    assert(task->getStatus() == status);
    assert(task->getDone() == done);

    task->setDateDue(time(0) + 1000);
    task->setStatus("Done");
    task->setDone(true);
    assert(task->getDateDue() != dueDate);
    assert(task->getStatus() != status);
    assert(task->getDone() != done);

    assert(task->getId() == 1);
    assert(task->getCount() == 1);

    vector<Task*> tasks;
    for(int i = 0; i < 10; ++i) {
        tasks.push_back(new Task("Task" + to_string(i + 1), "In Progress"));
    }
  
    assert(tasks[9]->getId() == 11);
    delete task;
    assert(task->getCount() == 10);
    task = new Task("Task11", "In Progress");
    assert(task->getId() == 12);

    string comment = "Comment1";
    task->addComment(comment);
    assert(task->comments[0] == comment);
    assert(task->getCommentQuont() == 1);
    task->deleteComment(0);
    assert(task->getCommentQuont() == 0);

    assert(tasks[9]->getDiagnostics() == "ID: 11\nName: Task10\nDate Created: " + to_string(tasks[9]->getDateCreated()) + "\nDate Due: " + to_string(tasks[9]->getDateDue()) + "\nStatus: In Progress\nDone: 0\n\n");

    cout << "All assert checks passed successfully!" << endl;
    return 0;
};