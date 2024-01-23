#include <iostream>
#include <string>
#include <cstring>
class CustomStack {
public:
    CustomStack(){}
    CustomStack(int maxSize) {
        sizeOfStack = 0;
        mData = new int[maxSize];
    }

    ~CustomStack() {
        delete[] mData;
    }

    void push(int newElement) {
        mData[sizeOfStack] = newElement;
        sizeOfStack++;
    }

    void pop() {
        if(sizeOfStack==0){
            cout<<"error"<<endl;
            exit(0);
        }
        else
        {
            sizeOfStack--;
        }
    }

    int top() {
        if(sizeOfStack==0){
            cout<<"error"<<endl;
            exit(0);
        }
        else
        {
            return mData[sizeOfStack - 1];
        }
    }

    int size() {
        return sizeOfStack;
    }

    bool empty() {
        return sizeOfStack == 0;
    }

    void extend(int n) {
        int *data_ext = new int[sizeOfStack + n];
        copy(mData, mData + sizeOfStack, data_ext);
        delete[] mData;
        mData = data_ext;
    }

protected:
    int *mData;
    int sizeOfStack;
};
int main()
{
    const int len_input = 10;
    CustomStack stack(100);
    char comands[5][len_input] = {"cmd_push","cmd_pop","cmd_top",
                                  "cmd_size","cmd_exit"};
    int choice;
    char el_push[20];
    char input[len_input];
    while(true){
        cin >> input;
        if(!strcmp(input,comands[0])){
            cin >> el_push;
            choice = 1;
        }
        for(int j = 1;j<5;j++){
            if(!strcmp(input,comands[j])){
                choice = j+1;
            }
        }
        switch (choice) {
            case 1:
                stack.push(atoi(el_push));
                cout<<"ok"<<endl;
                break;
            case 2:

                cout << stack.top() << endl;
                stack.pop();
                break;
            case 3:
                cout << stack.top() << endl;
                break;
            case 4:
                cout << stack.size() << endl;
                break;
            case 5:
                cout << "bye\n";
                exit(0);
                break;
            default:
                cout << "try again\n";
        }
        choice = 0;
    }
    return 0;
}