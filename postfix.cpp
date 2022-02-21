#include<iostream>
#include<stack>
#include<math.h>
using namespace std;

double calculate_Postfix(string  post_exp) {

    stack <int> stack;
    int len = post_exp.length();
    int m[100] = {};
    int indeksi = 0;
    int b = 0;

    //aletaan looppaan stringiä läpi
    for (int i = 0; i < len; i++) {

        if (post_exp[i] >= '0' && post_exp[i] <= '9') {
            stack.push(post_exp[i] - '0');
            indeksi++;
        }

        // jos onkin operaattori (ei luku väliltä 0-9) niin toteutetaan operaatio
        else {
            int numero = len - indeksi;

            // otetaan stackista kaikki numerot m arrayhin
            int f = 0;
            while (!stack.empty()) {
                m[f] = { stack.top() };
                stack.pop();
                f++;
                /*
                for (int f = 0; f < indeksi; f++) {
                    m[f] = { stack.top() };
                    stack.pop();
                }*/
            }
            f = 0;
            int laskin = indeksi - 1;
            switch (post_exp[i]) {

            case 'x': //swap 
                for (int f = 0; f < indeksi; f++) {
                    stack.push(m[f]);
                    laskin++;
                }
                f = 0;
                break;

            case 's': // sum
                for (int f = 0; f < len - numero; f++) {
                    b = b + m[f];
                }
                f = 0;
                stack.push(b);
                break;
            case '+':
                for (int f = 0; f < len - numero; f++) {
                    b = b + m[f];
                }
                f = 0;
                stack.push(b);
                break;

            case '-':  //minus
            
                for (int f = 0; f < indeksi; f++) {
                    stack.push(m[f]);
                    laskin++;
                };
                f = 0;
                while (!stack.empty()) {
                    m[f] = { stack.top() };
                    stack.pop();
                    f++;
                    /*
                    for (int f = 0; f < indeksi; f++) {
                        m[f] = { stack.top() };
                        stack.pop();
                    }*/
                };
                f = 0;
                b = m[0];
                for (int y = 1; y < indeksi; y++) { //len-numero                   
                    b = b - (m[y]);
                };
                stack.push(b);

                f = 0;
                break;
            
            case'a': //average
                for (int f = 0; f < len - numero; f++) {
                    b = b + m[f];
                };
                b = b / indeksi;
                f = 0;
                stack.push(b);
                break;

            case'*': //average
                b = m[0];
                for (int f = 0; f < len - numero; f++) {

                    b = b + m[f];
                };
                b = b / indeksi;
                f = 0;
                stack.push(b);
                break;
            
        }
            //puhdistetaan m-taulukko, jotta vanhat numerot eivät jää kummittelemaan
            for (int x = 0; x < indeksi+1; x++) {
                m[x] = 0;
            }
            
            indeksi = 1;    
        }
    }
    return stack.top();
}

int main(int argc, char* argv[]) {

    string postfix_expression = argv[1];
    //string postfix_expression = "13+7-";
    //string postfix_expression = "123a";
    //string postfix_expression = "12x-";
    //string postfix_expression = "123-";
    //string postfix_expression = "p";
    if (postfix_expression == "p") {
        cout << "Syota numerot ja taman jalkeen operaattori esim. '123+4-'" << endl;
        cout << "Operaattorit ovat:\n + = pluslasku\n s = pluslasku\n - = miinuslasku\n x = vaihtaa kaksi ylinta lukua\n a = keskiarvo \n * = kertolasku\n / = jakolasku\n % = jakojaannos \n ^ = potenssi\n v = neliojuuri\n Aja ohjelma uudelleen" << endl;
    }
    else {
        cout << "The answer after calculating the postfix expression is : ";
        cout << calculate_Postfix(postfix_expression) << endl;
    }
    return 0;
}