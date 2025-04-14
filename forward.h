#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
class ForwardList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;

        Node():data(T()),next(nullptr){}

        Node(T value):data(value),next(nullptr){}

        void killSelf(){
            if(next!=nullptr){
                next->killSelf();
            }
            delete this;
        }
    };
private:
    Node* head;
    int nodes;

public:
    ForwardList() : List<T>(), head(nullptr), nodes(0) {}

    ~ForwardList(){clear();}

    T front() override{
        if(head==nullptr) {
            throw runtime_error("Lista vacia");
        }
        return head->data;
    }

    T back() override{
        if(head==nullptr)
            throw runtime_error("Lista vacia");
        Node* current=head;
        while(current->next!=nullptr){
            current=current->next;
        }
        return current->data;
    }

    void push_front(T data) override{
        Node* newNode = new Node(data);
        newNode->next=head;
        head=newNode;
        nodes++;
    }

    void push_back(T data) override{
        Node* newNode = new Node(data);
        if(head==nullptr){
            head=newNode;
        }else{
            Node* current=head;
            while(current->next!=nullptr){
                current=current->next;
            }
            current->next=newNode;
        }
        nodes++;

    }

    T pop_front() override{
        if(head==nullptr){
            throw runtime_error("sin definir");
        }
        Node* temp=head;
        T data=temp->data;
        head=head->next;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() override{
        if(head==nullptr){
            throw runtime_error("sin definir");}
        if(head->next==nullptr){
            return pop_front();
        }
        Node* current=head;
        while(current->next->next != nullptr) {
            current = current->next;
        }
        T data = current->next->data;
        delete current->next;
        current->next = nullptr;
        nodes--;
        return data;
    }

    bool insert(T data, int pos) override{
        if(pos<0||pos>nodes){
            throw out_of_range("fuera de rango");
        }
        if(pos==0){
            push_front(data);
            nodes++;
        }else if(pos==nodes){
            push_back(data);
            nodes++;
        }else{
            Node* newNode= new Node(data);
            Node* current= head;
            for(int i=0;i<pos-1;i++){
                current=current->next;
            }
            newNode->next=current->next;
            current->next=newNode;
            nodes++;
        }return true;
    }

    bool remove(int pos) override {
        if(pos < 0 || pos >= nodes) {
            throw out_of_range("Posicion fuera de rango");
        }
        if(pos == 0) {
            pop_front();
        } else {
            Node* current = head;
            for(int i = 0; i < pos-1; ++i) {
                current = current->next;
            }
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            nodes--;
        }
        return true;
    }

    T& operator[](int pos) override {
        if (pos < 0 || pos >= nodes) {
            throw out_of_range("Indice fuera de rango");
        }

        Node* current = head;
        for (int i = 0; i < pos && current != nullptr; ++i) {
            current = current->next;
        }

        return current->data;
    }


    bool is_empty() override{
        return head== nullptr;
    }

    int size() override{
        return nodes;
    }

    void clear() override {
        while(head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        nodes = 0;
    }

    void sort() override{
        if(head == nullptr || head->next == nullptr) return;

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            Node* prev = nullptr;

            while(current->next != nullptr) {
                if(current->data > current->next->data) {

                    Node* nextNode = current->next;
                    current->next = nextNode->next;
                    nextNode->next = current;

                    if(prev == nullptr) {
                        head = nextNode;
                    } else {
                        prev->next = nextNode;
                    }

                    prev = nextNode;
                    swapped = true;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        } while(swapped);
    }

    bool is_sorted() override {
        if(head == nullptr || head->next == nullptr) {
            return true;
        }
        Node* current = head;
        while(current->next != nullptr) {
            if(current->data > current->next->data) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    void reverse() override {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while(current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }


    std::string name() override{
        return "ForwardList";
    }

};

#endif