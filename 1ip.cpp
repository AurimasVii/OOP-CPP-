//Aurimas Vižinis
#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <cassert>
using namespace std;

class Task {
private:
    static int count;
    static int nextId;
    int id;
    string name;
    string status;
    int dateCreated;
    int dateDue;
    bool done;
    vector<string> comments;

    void init(string name, string status, time_t dateCreated, time_t dateDue, bool done) {
        this->id = nextId++;
        count++;
        this->name = name;
        this->status = status;
        this->dateCreated = dateCreated;
        this->dateDue = dateDue;
        this->done = done;
    }

public:
    Task(string name, string status) {
        init(name, status, time(0), time(0), false);
    }

    Task(string name, string status, time_t dateCreated, time_t dateDue, bool done) {
        init(name, status, dateCreated, dateDue, done);
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

    string getName() const {
        return name;
    }

    int getDateCreated() const {
        return dateCreated;
    }

    int getDateDue() const {
        return dateDue;
    }

    string getStatus() const {
        return status;
    }

    bool getDone() const {
        return done;
    }

    int getCommentQuont() const {
        return comments.size();
    }

    int getId() const {
        return id;
    }

    static int getCount() {
        return count;
    }

    vector<string> getComments() const {
        return comments;
    }

    string getDiagnostics() const {
        stringstream ss;
        ss << id << " " << name << " " << dateCreated << " " << dateDue << " " << status << " " << done << " ";
        for (const auto& comment : comments) {
            ss << comment << " ";
        }
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

    task = new Task(name, status, createdDate, dueDate, done);

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
    assert(Task::getCount() == 10);
    task = new Task("Task11", "In Progress");
    assert(task->getId() == 12);

    string comment = "Comment1";
    task->addComment(comment);
    assert(task->getComments()[0] == comment);
    assert(task->getCommentQuont() == 1);
    task->deleteComment(0);
    assert(task->getCommentQuont() == 0);

    assert(tasks[9]->getDiagnostics() == ("11 Task10 " + to_string(tasks[9]->getDateCreated()) + " " + to_string(tasks[9]->getDateDue()) + " In Progress 0 "));

    for (Task* t : tasks) {
        delete t; 
    }
    tasks.clear();
    delete task;
    assert(Task::getCount() == 0);
    return 0;
};