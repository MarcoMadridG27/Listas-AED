#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
using namespace std;
template <typename T>
class CircularList : public List<T> {  
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;

            Node() : data(T()), next(nullptr), prev(nullptr){}

            Node(T value) : data(value), next(nullptr), prev(nullptr){
            }

            void killSelf(){
                if (next != nullptr) {
                    next->killSelf();
                    next = nullptr;
                }
                if (prev != nullptr) {
                    prev->killSelf();
                    prev = nullptr;
                }
                delete this;
            }    
        };

    private:
        Node* head;//sentinel
        int nodes; 

    public:
        CircularList() : List<T>() , nodes(0){
            head = new Node();  // centinela
            head->next = head;
            head->prev = head;
        }



        ~CircularList(){
            clear();
            delete head;
        }       

         T front() override {
             if (is_empty()) throw runtime_error("Lista vacía");
             return head->next->data;
        }

        T back() override {
            if (is_empty()) throw runtime_error("Lista vacía");
            return head->prev->data;
        }

        void push_front(T data) override {
            Node* newNode = new Node(data);
            newNode->next = head->next;
            newNode->prev = head;
            head->next->prev = newNode;
            head->next = newNode;
            nodes++;
        }

        void push_back(T data) override{
            Node* newNode = new Node(data);
            newNode->prev = head->prev;
            newNode->next = head;
            head->prev->next = newNode;
            head->prev = newNode;
            nodes++;
        }

        T pop_front() override{
            if (is_empty()) throw runtime_error("Lista vacía");
            Node* temp = head->next;
            T data = temp->data;
            head->next = temp->next;
            temp->next->prev = head;
            delete temp;
            nodes--;
            return data;
        }

        T pop_back() override {
            if (is_empty()) throw runtime_error("Lista vacía");
            Node* temp = head->prev;
            T data = temp->data;
            head->prev = temp->prev;
            temp->prev->next = head;
            delete temp;
            nodes--;
            return data;
        }

        bool insert(T data, int pos){
            if (pos < 0 || pos > nodes) throw out_of_range("fuera de rango");

            Node* newNode = new Node(data);
            Node* curr = head;

            for (int i = 0; i < pos; ++i) {
                curr = curr->next;
            }

            newNode->next = curr->next;
            newNode->prev = curr;
            curr->next->prev = newNode;
            curr->next = newNode;
            nodes++;
            return true;
        }

        bool remove(int pos) override{
            if (pos < 0 || pos >= nodes) throw out_of_range("fuera de rango");

            Node* curr = head->next;
            for (int i = 0; i < pos; ++i) {
                curr = curr->next;
            }

            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            nodes--;
            return true;
        }
    T& operator[](int pos)override{
        if (pos < 0 || pos >= nodes) throw out_of_range("fuera de rango");

        Node* curr = head->next;
        for (int i = 0; i < pos; ++i) {
            curr = curr->next;
        }
        return curr->data;
        }

    bool is_empty() override {
            return nodes == 0;
        }

    int size() override {
            return nodes;
        }

    void clear() override {
            while (!is_empty()) {
                pop_front();
            }
        }

    void sort() override {
            if (nodes < 2) return;

            bool swapped = true;
            while (swapped) {
                swapped = false;
                Node* curr = head->next;

                for (int i = 0; i < nodes - 1; ++i) {
                    if (curr->data > curr->next->data) {
                        std::swap(curr->data, curr->next->data);
                        swapped = true;
                    }
                    curr = curr->next;
                }
            }
        }

    bool is_sorted()override{
            if (is_empty()) return true;

            Node* curr = head->next;
            while (curr->next != head) {
                if (curr->data > curr->next->data) return false;
                curr = curr->next;
            }
            return true;
        }

    void reverse() override {
            if (nodes < 2) return;

            Node* curr = head;
            do {
                std::swap(curr->next, curr->prev);
                curr = curr->prev;
            } while (curr != head);
        }

    std::string name(){
            return "CircularList";
        }
};


#endif