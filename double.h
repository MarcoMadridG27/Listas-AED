#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class DoubleList : public List<T> {
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;

            Node():data(T()), next(nullptr), prev(nullptr) {}

            Node(T value):data(value),next(nullptr),prev(nullptr){}

            void killSelf(){
                if(next!=nullptr) {
                    next->killSelf();
                }
                delete this;
            }
        };

    private:
        Node* head;
        Node* tail;
        int nodes;

    public:
        DoubleList() : List<T>(), head(nullptr), tail(nullptr), nodes(0) {}

        ~DoubleList(){ 
         	clear();
        }

         T front() override {
            if(is_empty()) throw std::runtime_error("Lista vacia");
            return head->data;
        }

        T back(){
            if(is_empty()) throw std::runtime_error("Lista vacia");
            return tail->data;
        }

        void push_front(T data){
            Node* newNode=new Node(data);
            newNode->next=head;
            if(head) head->prev=newNode;
            else tail = newNode;
            head = newNode;
            nodes++;
        }

        void push_back(T data){
            Node* newNode=new Node(data);
            if(tail==nullptr) head=tail=newNode;
            else {
                tail->next=newNode;
                newNode->prev=tail;
                tail=newNode;
            }
            nodes++;
        }

        T pop_front() override {
            if(is_empty()) throw std::runtime_error("Lista vacia");
            Node* temp=head;
            T data=temp->data;
            head=head->next;
            if(head) head->prev=nullptr;
            else tail=nullptr;
            delete temp;
            nodes--;
            return data;
        }

        T pop_back(){
            if(is_empty()) throw std::runtime_error("Lista vacia");
            if(head==tail) return pop_front();
            Node* temp=tail;
            T data=temp->data;
            tail=tail->prev;
            tail->next=nullptr;
            delete temp;
            nodes--;
            return data;
        }

    bool insert(T data, int pos) override {
            if(pos<0 || pos>nodes) throw std::out_of_range("fuera de rango");

            Node* newNode=new Node(data);

            if(pos==0) {
                newNode->next=head;
                if(head!=nullptr) head->prev=newNode;
                else tail=newNode;
                head=newNode;
            } else if(pos==nodes) {
                newNode->prev=tail;
                if(tail!=nullptr) tail->next=newNode;
                else head=newNode;
                tail=newNode;
            } else {
                Node* temp=head;
                int i=0;
                while(i<pos-1) {
                    temp=temp->next;
                    i++;
                }
                newNode->next=temp->next;
                newNode->prev=temp;
                temp->next->prev=newNode;
                temp->next=newNode;
            }
            nodes++;
            return true;
        }


        bool remove(int pos) override {
            if(pos<0 || pos>=nodes) throw std::out_of_range("fuera de rango");
            if(pos==0) pop_front();
            else if(pos==nodes-1) pop_back();
            else {
                Node* current=head;
                for(int i=0; i<pos;++i) {
                    current=current->next;
                }
                current->prev->next=current->next;
                current->next->prev=current->prev;
                delete current;
                nodes--;
            }
            return true;
        }

        T& operator[](int pos) override {
            if(pos<0 || pos>=nodes) throw std::out_of_range("fuera de rango");
            Node* current=head;
            for(int i=0;i<pos;++i) {
                current=current->next;
            }
            return current->data;
        }

        bool is_empty() override {
            return head == nullptr;
        }

        int size() override {
            return nodes;
        }

        void clear(){
            while(head!=nullptr) {
                Node* temp=head;
                head=head->next;
                delete temp;
            }
            tail=nullptr;
            nodes=0;
        }
        
        void sort() override {
            if(!head || !head->next) return;

            bool swapped=true;

            while(swapped) {
                swapped=false;
                Node* current=head;

                while(current->next) {
                    if(current->data > current->next->data) {
                        std::swap(current->data, current->next->data);
                        swapped=true;
                    }
                    current=current->next;
                }
            }

            Node* temp=head;
            while(temp->next) {
                temp=temp->next;
            }
            tail=temp;
        }


        bool is_sorted() override {
            Node* temp=head;
            while(temp && temp->next) {
                if(temp->data>temp->next->data) return false;
                temp=temp->next;
            }
            return true;
        }

        void reverse() override {
            Node* current=head;
            Node* temp=nullptr;

            while(current!=nullptr) {
                temp=current->prev;
                current->prev=current->next;
                current->next=temp;
                current=current->prev;
            }

            if(temp) {
                tail=head;
                head=temp->prev;
            }

        }

        std::string name() override {
            return "DoubleList";
        }
        
};
#endif

