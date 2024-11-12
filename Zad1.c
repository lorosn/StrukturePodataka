#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	double data;
	struct Node* next;
} Node;

int initializeStack(Node** stack);
int push(Node** stack, double value);
int pop(Node** stack, double* result);
double evaluatePostfix(FILE* filePointer);

int main() {
	FILE* file = fopen("postfix.txt", "r");
	if (file == NULL) {
		printf("File opening error!\n");
		return EXIT_FAILURE;
	}
	double result = evaluatePostfix(file);

	printf("Rezultat of postfix term: %.2lf\n", result);

	fclose(file);

	return EXIT_SUCCESS;
}

int initializeStack(Node** stack) {
	*stack = NULL;
	return 1;
}

int push(Node** stack, double value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		printf("Error allocating memory!\n");
		return 0;
	}

	newNode->data = value;
	newNode->next = *stack;
	*stack = newNode;

	return 1;
}

int pop(Node** stack, double* result) {
	if (!*stack) {
		printf("Stack is empty!\n");
		return 0;
	}

	Node* top = *stack;
	*result = top->data;
	*stack = top->next;
	free(top);

	return 1;
}

double evaluatePostfix(FILE* filePointer) {
	Node* stack;
	if (!initializeStack(&stack)) {
		printf("Stack initialization error!\n");
		return EXIT_FAILURE;
	}

	char token[20];
	while (fscanf(filePointer, "%s", token) != EOF) {
		if (token[0] >= '0' && token[0] <= '9') {
			double value = atof(token);
			if (!push(&stack, value)) {
				printf("Adding stack element error.\n");
				return EXIT_FAILURE;
			}
		}
		else {
			double operand2, operand1;
			if (!pop(&stack, &operand2) || !pop(&stack, &operand1)) {
				printf("Removing stack element error.\n");
				return EXIT_FAILURE;
			}

			switch (token[0]) {
			case '+':
				if (!push(&stack, operand1 + operand2)) {
					printf("Error adding result back on stack.\n");
					return EXIT_FAILURE;
				}
				break;
			case '-':
				if (!push(&stack, operand1 - operand2)) {
					printf("Error adding result back on stack.\n");
					return EXIT_FAILURE;
				}
				break;
			case '*':
				if (!push(&stack, operand1 * operand2)) {
					printf("Error adding result back on stack.\n");
					return EXIT_FAILURE;
				}
				break;
			case '/':
				if (operand2 == 0) {
					printf("Division by zero isn't allowed!\n");
					return EXIT_FAILURE;
				}
				if (!push(&stack, operand1 / operand2)) {
					printf("Error adding result back on stack.\n");
					return EXIT_FAILURE;
				}
				break;
			default:
				printf("Unknown operator: %s\n", token);
				return EXIT_FAILURE;
			}
		}
	}

	double result;
	if (!pop(&stack, &result)) {
		printf("Invalid postfix term.\n");
		return EXIT_FAILURE;
	}

	if (stack != NULL) {
		printf("Invalid postfix term.\n");
		return EXIT_FAILURE;
	}

	return result;
}
