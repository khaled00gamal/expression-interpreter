#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef union {
    float fData;
    char cData;
} Item;
typedef struct Node Node;
struct Node {
    Node *next;
    Node *prev;   //for doubly linked list implementation of Stack
    Item data;
};
typedef struct {
    Node *top;
} Stack;
typedef struct BSTNode BSTNode;

struct BSTNode {
    float value;
    char *key;      //Binary tree
    BSTNode *left;
    BSTNode *right;
};
typedef struct Heap Heap;
struct Heap {
    int size;
    BSTNode *array;
};

Stack *initialize();

int isEmpty(Stack *s);

Item top(Stack *s);

Item pop(Stack *s);

void push(Stack *s, Item data);

void infixToPostfix(char *infix, char *postfix);

float evaluatePostfix(char *postfix, BSTNode *root);

void replaceNewLineBySpace(char *s);

int pcheck(char a, char b);  //to check operators precedence

void deblank(char str[]);  //remove spaces from sentences

Node *newNode(Item data);

void printStack(Stack *s);

BSTNode *newBSTNode(char *k, float v);

Heap *newHeap(BSTNode *bstNode);

BSTNode *put(BSTNode *root, char *k, float v);

BSTNode *search(BSTNode *root, char *key);

void inOrder(BSTNode *root);

void interpeter();

char *deblank2(char *input); //remove spaces from sentences

int count(BSTNode *node);

void swap(BSTNode *node1, BSTNode *node2);

void heapSort(BSTNode *array, int size);

void heapify(BSTNode array[], int size, int i);

int copyToArray(BSTNode *node, BSTNode *array, int index);

void validateEqual(char buffer[]);

void checkParentheses(char *string);

void validateOneVariableOnly(char *string);

BSTNode *deleteBSTNode(BSTNode *root, char *key);

BSTNode *getMin(BSTNode *root);

int main() {
    interpeter(); //reads file and prints out everything
}

void interpeter() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("file not found");
        return;
    }
    char buffer[1000];//to read lines from file
    char variableName[100];//to store variable name
    char expression[100];//to store infix expression
    char postfix[1000];//to store infix to postfix in
    BSTNode *root = NULL;
    printf("input.txt\n\n");
    while (!feof(fp)) {
        strcpy(postfix, ""); // initializes postfix for each line
        fgets(buffer, 1000, fp); //reads nth line
        replaceNewLineBySpace(buffer); //fixes
        printf("%s\n", buffer);
        validateEqual(buffer);
        char *token = strtok(buffer, "="); //to store the variable name(everything before equal)
        validateOneVariableOnly(token);
        strcpy(variableName, deblank2(token));//stores the token and removes spaces from it
        token = strtok(NULL, "\n"); //takes the infix part of the expression(after = till end of line)
        strcpy(expression, token);//stores it in an expression which will be converted to postfix
        checkParentheses(expression);
        infixToPostfix(expression, postfix);//converts expression to postfix
        if (!strcmp(variableName, search(root, variableName)->key))//if variable exists,delete its old value
            root = deleteBSTNode(root, variableName);
        root = put(root, variableName, evaluatePostfix(postfix,
                                                       root));//evaluates the expression and stores name,value of variable then inserts it to the BST

    }
    printf("\n\nVariables sorted by name:\n\n");
    inOrder(root);//prints the variable values sorted by variable name
    printf("\n");
    Heap *heap = newHeap(root);
    copyToArray(root, heap->array, 0);
    heapSort(heap->array, heap->size);
    int i;
    printf("Variables sorted by value:\n\n");
    for (i = 0; i < heap->size; i++)
        printf("%s = %0.2f \n", heap->array[i].key, heap->array[i].value);
}


int copyToArray(BSTNode *node, BSTNode *array, int index) {
    if (node == NULL)
        return index;
    array[index].value = node->value;
    array[index].key = malloc(sizeof(node->key));
    strcpy(array[index].key, node->key);
    index++;
    if (node->left != NULL)
        index = copyToArray(node->left, array, index);
    if (node->right != NULL)
        index = copyToArray(node->right, array, index);
    return index;
}

void swap(BSTNode *node1, BSTNode *node2) {
    BSTNode tempNode = *node1;
    *node1 = *node2;
    *node2 = tempNode;
}


void heapify(BSTNode array[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && array[left].value > array[largest].value)
        largest = left;

    if (right < size && array[right].value > array[largest].value)
        largest = right;

    if (largest != i) {
        swap((BSTNode *) &array[i].value, (BSTNode *) &array[largest].value);

        heapify(array, size, largest);
    }
}

void heapSort(BSTNode *array, int size) {
    // rearrange array
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);
    for (int i = size - 1; i >= 0; i--) {
        // move current root to end
        swap((BSTNode *) &array[0].value, (BSTNode *) &array[i].value);
        heapify(array, i, 0);
    }

}


void infixToPostfix(char *infix, char *postfix) {
    Stack *s = initialize();
    deblank(infix); //removes spaces from the infix so that it doesn't matter whether its with spaces or not
    char operator[2];
    char operand[2];
    operator[1] = '\0';
    operand[1] = '\0';
    char next[2];     //all of those variables are used so we can use strcat and atoi for characters
    next[1] = '\0';
    char prev[2];
    prev[1] = '\0';
    Item c;
    int i = 0;
    while (infix[i] != '\0') {
        prev[0] = infix[i -
                        1]; //for checking that the - is an operator later on(if what's before it is a number or a variable name,its for sure an operator)
        if (infix[i] == '(') {
            c.cData = infix[i];
            push(s, c);
        } else if (infix[i] == ')') {
            while (!isEmpty(s) && top(s).cData != '(') {
                operator[0] = pop(s).cData;
                strcat(postfix, operator);
                strcat(postfix, " ");
            }
            pop(s); //to get rid of opening bracket
        } else if (infix[i] == '+' || (infix[i] == '-' && (atoi(prev) || isalpha(prev[0]))) || infix[i] == '*' ||
                   infix[i] == '/' ||
                   //the && is responsible for checking that the that the - sign is an operator not part of a number
                   infix[i] == '^') {
            while (!isEmpty(s) && top(s).cData != '(' && pcheck(top(s).cData, infix[i])) {
                operator[0] = pop(s).cData;
                strcat(postfix, operator);
                strcat(postfix, " ");
            }
            c.cData = infix[i];
            push(s, c);
        } else {
            operand[0] = infix[i];
            next[0] = infix[i + 1];
            strcat(postfix, operand);
            if (infix[i + 1] != '.' && !atoi(next) && next[0] != '0' && !isalpha(
                    next[0])) //makes sure that a space is only added at the end of the full number or full variable name
                strcat(postfix, " ");
        }
        i++;
    }
    while (!isEmpty(s)) {
        operator[0] = pop(s).cData;
        strcat(postfix, operator);
        strcat(postfix, " ");
    }


}

float evaluatePostfix(char *postfix, BSTNode *root) {
    char *token;
    Item pushed, x, y, result;
    Stack *s = initialize();
    token = strtok(postfix, " ");
    while (token != NULL) {
        if (token[0] == '+' || (token[0] == '-' && !atof(token)) || token[0] == '*' || token[0] == '/' ||
            token[0] ==
            '^') { //the && is reposible for checking that the - sign is an operator(if token isn't a number atof is zero)
            y.fData = pop(s).fData;
            x.fData = pop(s).fData;
            if (token[0] == '+')
                result.fData = x.fData + y.fData;
            else if (token[0] == '*')
                result.fData = x.fData * y.fData;
            else if (token[0] == '-')
                result.fData = x.fData - y.fData;
            else if (token[0] == '/')
                result.fData = x.fData / y.fData;
            else if (token[0] == '^')
                result.fData = pow(x.fData, y.fData);
            push(s, result);
        } else {
            if (!atof(token) &&
                strcmp(token, "0")) //if variable name and not zero,replace the variable name with its value
            {
                BSTNode *searchResult = search(root, token);
                if (!strcmp(searchResult->key,
                            token)) //searches for the variable in the bst and compares it with the token
                    pushed.fData = searchResult->value;
                else {
                    printf("%s not declared", token); //if variable isn't found in the BST , generate an error
                    exit(0);
                }
            } else
                pushed.fData = atof(token);
            push(s, pushed);
        }
        token = strtok(NULL, " ");
    }
    return top(s).fData;
}

Stack *initialize() {
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

Node *newNode(Item data) {
    Node *n = malloc(sizeof(Node));
    n->next = n->prev = NULL;
    n->data = data;
    return n;
}

int isEmpty(Stack *s) {
    if (!s->top)
        return 1;
    return 0;
}

Item top(Stack *s) {
    if (isEmpty(s))
        exit(0);
    return s->top->data;
}

Item pop(Stack *s) {
    if (isEmpty(s))
        exit(0);
    Item temp = s->top->data;
    Node *t = s->top;
    if (!s->top->prev)
        s->top = NULL;
    else {
        s->top = s->top->prev;
        s->top->next = NULL;
    }
    free(t);
    return temp;
}

void push(Stack *s, Item x) {
    Node *n = newNode(x);
    if (isEmpty(s))
        s->top = n;
    else {
        n->prev = s->top;
        s->top->next = n;
        s->top = n;
    }
}

void printStack(Stack *s) {
    Stack *temp = initialize();
    while (!isEmpty(s)) {
        push(temp, pop(s));
        printf("%f\t", top(temp).fData);
    }
    while (!isEmpty(temp)) {
        push(s, pop(temp));
    }
}

BSTNode *newBSTNode(char *k, float v) {
    BSTNode *n = malloc(sizeof(BSTNode));
    n->left = n->right = NULL;
    n->key = malloc(strlen(k) + 1);
    n->value = v;
    strcpy(n->key, k);
    return n;
}

Heap *newHeap(BSTNode *bstNode) {
    Heap *newHeap = malloc(sizeof(Heap));
    newHeap->size = count(bstNode);
    newHeap->array = malloc(sizeof(BSTNode) * newHeap->size);
    // newHeap->array->key=malloc(sizeof(key));
    return newHeap;
}

BSTNode *put(BSTNode *root, char *k, float v) {
    if (!root) root = newBSTNode(k, v);
    else if (strcasecmp(k, root->key) < 0) root->left = put(root->left, k, v);
    else root->right = put(root->right, k, v);
    return root;
}


void inOrder(BSTNode *root) {
    if (root) {
        inOrder(root->left);
        printf("%s=%.2f\n", root->key, root->value);
        inOrder(root->right);
    }
}


BSTNode *search(BSTNode *root, char *key) {
    BSTNode *notfound = newBSTNode("not found", -999999);
    while (root) {
        if (!strcasecmp(key, root->key))
            return root;
        else if (strcasecmp(key, root->key) < 0)
            root = root->left;
        else root = root->right;
    }
    return notfound;
}


void deblank(char str[]) {
    char *token;
    char *str1 = (char *) malloc(100);
    strcpy(str1, str);
    strcpy(str, "");
    token = strtok(str1, " ");
    while (token != NULL) {
        strcat(str, token);
        token = strtok(NULL, " ");
    }

}

char *deblank2(char *input) {
    int i, j;
    char *output = input;
    for (i = 0, j = 0; i < strlen(input); i++, j++) {
        if (input[i] != ' ')
            output[j] = input[i];
        else
            j--;
    }
    output[j] = 0;
    return output;
}

void replaceNewLineBySpace(char *s) {
    char *s1 = s;
    while ((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int pcheck(char a, char b) {
    if (a == '+' || a == '-')
        a = 1;
    else if (a == '/' || a == '*')
        a = 2;
    else if (a == '^')
        a = 3;
    if (b == '+' || b == '-')
        b = 1;
    else if (b == '/' || b == '*')
        b = 2;
    else if (a == '^')
        b = 3;
    if (a == b) {
        if (a == '^')
            return 0;
        return 1;
    }
    return a > b ? 1 : 0;
}

int count(BSTNode *node) {
    if (node == NULL)
        return 0;
    else
        return 1 + count(node->left) + count(node->right);
}

void validateOneVariableOnly(char *string) {
    int i;
    while (string[i] != '\0') {
        if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/' || string[i] == '^') {
            printf("L.H.S can only contain one variable");
            exit(1);
        }
        i++;
    }
}

void validateEqual(char buffer[]) {
    int count = 0, i;
    for (i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == '=') {
            count++;
        }
    }
    if (count != 1) {
        printf("invalid input,check equal signs\n");
        exit(0);
    }
}


void checkParentheses(char *string) {
    Stack *stack = initialize();
    Item parenthesis;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '{' || string[i] == '[' || string[i] == '(') {
            parenthesis.cData = string[i];
            push(stack, parenthesis);
        } else if (string[i] == '}' || string[i] == ']' || string[i] == ')') {
            if (isEmpty(stack)) {
                printf("Parentheses are unbalanced\n");
                exit(0);
            } else if (top(stack).cData == '{') {
                if (string[i] == '}')
                    pop(stack);
                else {
                    printf("Parentheses are unbalanced\n");
                    exit(0);
                }
            } else if (top(stack).cData == '[') {
                if (string[i] == ']')
                    pop(stack);
                else {
                    printf("Parentheses are unbalanced\n");
                    exit(0);
                }
            } else if (top(stack).cData == '(') {
                if (string[i] == ')')
                    pop(stack);
                else {
                    printf("Parentheses are unbalanced\n");
                    exit(0);
                }
            }
        }
    }
    if (!isEmpty(stack)) {
        printf("Parentheses are unbalanced\n");
        exit(0);
    }
}

BSTNode *getMin(BSTNode *root) {
    BSTNode *min = NULL;
    while (root) {
        min = root;
        root = root->left;
    }
    return min;
}

BSTNode *deleteBSTNode(BSTNode *root, char *key) {
    if (root == NULL) return root;
    if (strcasecmp(key, root->key) < 0)
        root->left = deleteBSTNode(root->left, key);
    else if (strcasecmp(key, root->key) > 0)
        root->right = deleteBSTNode(root->right, key);

    else {
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }
        BSTNode *temp = getMin(root->right);
        root->key = temp->key;
        root->right = deleteBSTNode(root->right, temp->key);
    }
    return root;
}







