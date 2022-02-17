#include<iostream>
#include<stack>
#include<math.h>
using namespace std;

int calculate_Postfix(string  post_exp){

    stack <int> stack;
    int len = post_exp.length();
    int m[100] = {};
    int indeksi = 0;
    int b = 0;

    //aletaan looppaan stringiä läpi
    for (int i = 0; i < len; i++){   

        if (post_exp[i] >= '0' && post_exp[i] <= '9'){
            stack.push(post_exp[i] - '0');
            indeksi++;
        }

        // jos onkin operaattori (ei luku väliltä 0-9) niin toteutetaan operaatio
        else{   
            int numero = len - indeksi;

            // otetaan stackista kaikki numerot m arrayhin
            for (int f = 0; f < indeksi; f++) {
                m[f] = { stack.top() };
                stack.pop(); 
            }
            int laskin = indeksi-1;                     
                switch (post_exp[i]){

                case 'x': //swap 
                    for (int f = 0; f < indeksi; f++) {
                        stack.push(m[f]);
                        laskin++;
                    }
                    break;

                case 's': // sum
                    for (int f = 0; f < len - numero; f++) {
                        b = b + m[f];
                    }
                    stack.push(b);
                    break;

                case '-':  //minus
                    b = m[0];
                    for (int f = 1; f < len - numero; f++) {
                        b = (m[f])-b;
                    }
                    stack.push(b);
                    break;

                case'a': //average
                    for (int f = 0; f < len - numero; f++) {
                        b = b + m[f];
                    };
                    b = b / indeksi;
                    stack.push(b);
            }
        }   
    }
    return stack.top();
}

int main(int argc, char* argv[]){
    
    string postfix_expression = argv[1];
    //string postfix_expression = "123a";
    //string postfix_expression = "123s";
    //string postfix_expression = "12x-";

    cout << "The answer after calculating the postfix expression is : ";
    cout << calculate_Postfix(postfix_expression) << endl;
    return 0;
}