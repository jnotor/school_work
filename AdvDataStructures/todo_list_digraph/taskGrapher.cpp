#include <iostream>
#include <list>
#include <stdbool.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <vector>

// ADT to contain the nodes of the DAG
struct node{
    std::string task_name = "";
    int task_number;
    bool visited = false;
    int topSortLabel = -1;
    node* next = nullptr;
};

// ADT to contain the nodes of the topologically sorted linked list
struct tSNode {
    std::string task_name = "abc";
    int topSortLabel;
    tSNode* next = nullptr;
};


/** Helper function for parsing string to int
 * @param s: const. string to be parsed
 * @param task_relations: vector of strings containing numbers in pairs,
 *                        seperated by spaces
 */
std::vector<int> string_split(const std::string& s, char delimiter) {
    std::vector<int> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        std::stringstream t_var(token);
        int x;
        t_var >> x;
        tokens.push_back(x);
    }
    return tokens;
}

/** Helper function to print out the Adjacency list representation of the
 * Digraph's vertices
 */
void printList(node* ptr) {
    node* temp = ptr;
    while (temp != nullptr) {
		std::cout << " -> " << temp->task_name << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}


// Class to implement the directed graph
class Digraph{
    // number of nodes in the graph
    int numVerts;

    // delimiter used to parse user input for task relaitons
    char delim = ' ';

public:
    // An array of pointers to Node to represent adjacency list
    node** head;


    /** Constructor. Initializes array of of vertice nodes
     * @param tasks: vector of strings containing tasks names for each vertice
     *               at vertice number equal to their position in the vector
     * @param task_relations: vector of strings containing numbers in pairs,
     *                        seperated by spaces, i.e. "3 1" means edge from
     *                        vertice 3 to 1
     */
    Digraph(std::vector<std::string> tasks, std::vector<std::string> task_relations) {
        // allocate memory
        int N = tasks.size();
        head = new node*[N]();
        this->numVerts = N;

        // init head pointer for all vertices
        for (int i = 0; i < N; i++) {
            // below is working inconsistently for some reason
            head[i] = new node;
            head[i]->task_name = tasks[i];
            head[i]->task_number = i;
            head[i]->visited = false;
            head[i]->next = nullptr;
        }

        // add edges for directed graph
        for (int i = 0; i < task_relations.size(); i++) {
            this->edge_adder(task_relations[i]);
        }
    }





    /** Method to check for a cycle in the directed graph; determines if DAG or not.
     * @param: topologically sorted LL containing nodes with top sort labels and task names
     *
     * return: bool. True if cycle found, false if not.
     */
    bool cycle_checker(tSNode* TS_LL_head) {
        // First we need to give the Top Sort Label number to each node in the DAG

        // iterate through the pointer array to get to each vertex and it's adj LL
        for (int i = 0; i < this->numVerts; i++) {

            // iterate through the LL at position i
            node* adj_current_node = head[i];
            while (adj_current_node != nullptr){

                // iterate through the TS LL
                tSNode* TS_current_node = TS_LL_head;
                while (TS_current_node != nullptr){
                    // If we find a pair of nodes with the same task name
                    if (adj_current_node->task_name == TS_current_node->task_name) {
                        // Assign the top sort label from the TS LL to that DAG adjency node
                        adj_current_node->topSortLabel = TS_current_node->topSortLabel;
                        break;
                    }
                    TS_current_node = TS_current_node->next;
                }
                adj_current_node = adj_current_node->next;
            }
        }

        // Then we need to perform the actual cycle check
        for (int i = 0; i < this->numVerts; i++) {
            node* ccheck_head = head[i];
            node* ccheck_node = head[i];

            while (ccheck_node != nullptr) {
                // if the tail of any edge is greater than the label on its head,
                // the Digraph is cyclic
                if (ccheck_head->topSortLabel > ccheck_node->topSortLabel) {
                    // Useful print statements for debugging
                    // std::cout << "previous: " << ccheck_head->topSortLabel << " . Current: " << ccheck_node->topSortLabel << std::endl;
                    // std::cout << "previous name: " << ccheck_head->task_name << " . Current name: " << ccheck_node->task_name << std::endl;
                    return true;
                }
                ccheck_node = ccheck_node->next;
            }
        }
        return false;
    }


    /** Method employed to add edges. Takes a given task relation set and creates
     *  new edge from edge_to_add[0] -> new edge from edge_to_add[1]
     * @param edge_to_add: string of an edge to add
     */
    void edge_adder(std::string edge_to_add) {
        // parse user input from string to edges
        std::vector<int> edge;
        edge = string_split(edge_to_add, this->delim);
        int src = edge[0];
        int dest = edge[1];

        if (head[src] != nullptr) {
            node* newNode = new node;
            newNode->task_name = head[dest]->task_name;
            newNode->task_number = head[dest]->task_number;
            newNode->visited = false;
            newNode->next = nullptr;

            node* temp = head[src];
            while(temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }


    /** Method employed to delete edges. Takes a given task relation set and removes
     *  the edge from edge_to_rn[0] -> edge_to_rn[1]
     *
     * @param edge_to_rn: string of vert pair to remove where position 0 is from-vertice,
     *                    position 1 is a delim and position 2 is to-vertice (assuming
     *                    numbers are single digit in this example)
     */
    void edge_deleter(std::string edge_to_rn) {
        std::vector <int> edge_to_delete = string_split(edge_to_rn, this->delim);
        int src = edge_to_delete[0];
        int connection = edge_to_delete[1];

        node* ptr = head[src];
        while (ptr->next != nullptr) {
            if (ptr->next->task_number == connection) {
                // if the connection is at the end of the list
                if (ptr->next->next == nullptr) {
                    delete ptr->next;
                    ptr->next = nullptr;
                    break;
                }
                // if the connection is in the middle of the list
                else {
                    // store temp reference to current next node, the one we want to delete
                    node* temp = ptr->next;

                    // set current next node to be the next, next node
                    ptr->next = ptr->next->next;

                    // delete our node we want to remove edge to
                    delete temp;
                    break;
                }
            }
            ptr = ptr->next;
        }
    }


    /** Helper function for topological_sorter(). Recursively travels to nodes'
     *  nexts
     * @param counter: int counter for how many nodes we've visited; used for assiging
     *                 the new node in the topological sort LL a top. Sort label
     * @param current_node: node ptr to the current node in the DAG we're on/visiting
     * @param TS_LL: node ptr to the head of the topologically sorted LL
     */
    void topSortUtil(int counter, node* current_node, tSNode* TS_LL) {
    	// Mark the current node as visited.
        current_node->visited = true;

        // Recur for all verts adjacent to this vert
        node* temp = current_node;
        while (temp->next != nullptr) {
            temp = temp->next;
            int vertPos = temp->task_number;
            if (head[vertPos]->visited == false) {
                counter++;
                topSortUtil(counter, head[vertPos], TS_LL);
            }
        }

        tSNode* temp2 = new tSNode;
        temp2->task_name =  TS_LL->task_name;
        temp2->topSortLabel = TS_LL->topSortLabel;
        temp2->next = TS_LL->next;
        if (temp2->task_name != "abc") {
            // Add current vertex to the topSort LL
            TS_LL->task_name = current_node->task_name;
            TS_LL->topSortLabel = counter;
            TS_LL->next = temp2;
        }
        // Base case; found the bottom most member of TS LL
        else {
          TS_LL->task_name = current_node->task_name;
          TS_LL->topSortLabel = this->numVerts;
          TS_LL->next = nullptr;
        }
    }


    /** Method to topologically sort the Digraph. Also prints the sort and calls
     * the cycle check function to report to the user if the digraph is a DAG or
     * not
     */
    void topological_sorter() {
        // initialize an empty node to start the TS_LL
        tSNode* TS_LL = new tSNode;

        // iterate through head array, vert by vert
        int counter = 0;
        for (int i = 0; i < numVerts; i++){
            // if the vert isnt visted, call util function to dive deeper
            if (head[i]->visited == false) {
                topSortUtil(counter, head[i], TS_LL);
            }
        }

        // print the topSort LL
        tSNode* temp = TS_LL;
        while (temp != nullptr) {
            std::cout << temp->task_name << " ";
            temp = temp->next;
        }
        std::cout << "\n";

        // perform cycle check and report to user if cycle
        if (this->cycle_checker(TS_LL)) {
            std::cout << "ERROR: directed graph is not a DAG" << std::endl;
        }
    }


    /** Deconstructor for the Digraph class
     */
    ~Digraph() {
        for (int i = 0; i <this->numVerts; i++) {
            // initialize current node to head
            node* currentNode = head[i];
            while (currentNode != nullptr) {
                // get next node
                node* nextNode = currentNode->next;

                delete currentNode;

                // set current to "old" next
                currentNode = nextNode;
            }
        }
    }
};


// User Interface class
class UI {

public:
    /** Constructor method for user interaction. Gathers task names and relations.
     * Does some data validation in an attempt to disallow the user from entering
     * data that could elsewise break/crash the program or produce erroneous results
     */
    UI() {
        // user input storage vectors
        std::vector<std::string> user_tasks;
        std::vector<std::string> user_task_relations;

        // iterator declaration
        int i = 0;

        // boolean state holder
        bool complete = false;

        // user input checking variables
        std::string UserInput;
        std::string TestString;

        // Get tasks
        while (!complete) {
            std::cout << "Please enter task followed by the enter key. Type Done when complete \n";
            std::getline(std::cin, UserInput);

            if (UserInput.compare("Done") == 0 || UserInput.compare("done") == 0 || UserInput.compare("DONE") == 0 || UserInput.compare("") == 0) {
                complete = true;
            }
            else {
                user_tasks.push_back(UserInput);
            }
        }

        // print tasks and associated task numbers to users
        for (i = 0; i < user_tasks.size(); i++) {
            std::cout << user_tasks[i] << "    " << i << std::endl;
        }

        // Reset complete
        complete = false;

        // Get task relations
        while (!complete) {
            std::cout << "Please enter task relation that is space seperated followed by the enter key . Type Done when finished \n";
            std::getline(std::cin, UserInput);

            if (UserInput.compare("Done") == 0 || UserInput.compare("done") == 0 || UserInput.compare("DONE") == 0 || UserInput.compare("") == 0) {
                complete = true;
            }
            else if (validate_tasks(user_tasks, UserInput)) {
                std::cout << "Invalid Input, Try again" << std::endl;
            }
            else {
                user_task_relations.push_back(UserInput);
            }
        }

        // Call to Digraph constructor
        Digraph taskList(user_tasks, user_task_relations);

        // Output the topologically sorted LL to the user
        taskList.topological_sorter();

    }

    /** Helper method to validate tasks entered by the user. Checks include:
     *  -excluding non-numerical entries
     *  -excluding ill-formatted entries (example: "30 " or "0 1 2")
     *  -excluding numbers out of bounds/ less than 0 or greater than number of tasks
     *  -excluding duplicated numbers (i.e. "0 0")
     *  -
     * @param task_relations: vector of task relation strings entered by user
     * @param validation: string to check
     */
    bool validate_tasks(std::vector<std::string> task_relations, std::string validation) {
        // split the string in two
        std::vector <int> edge_to_check = string_split(validation, ' ');

        // check each of the two parts of the edge for validity.
        if (edge_to_check.size() > 2) {
            return true;
        }
        else if (!std::isdigit(validation[0]) || edge_to_check[0] > task_relations.size() || edge_to_check[0] < 0 || edge_to_check[0] == edge_to_check[1]) {
            return true;
        }
        else if (!std::isdigit(validation[2]) || edge_to_check[1] > task_relations.size() ||  edge_to_check[1] < 0) {
            return true;
        }
        return false;
    }
};

int main() {
    UI();
}
