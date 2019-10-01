struct Node{
    int store;
    Node* next_node;
    Node(int data = 0):store(data){}
    Node(int data, Node* next):store(data),next_node(next){}
};

class stack{
    private:
        Node* topNode;
        int Size;
    public:
        stack(int size = 0,Node* topNode = 0){}
        void push(int posy);
        int size();
        int top();
        bool isEmpty();
};