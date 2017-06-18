#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node;

int main() {
	char input[100001];
	char *p;			/* wsk na kolejny element z input */
	node *head = NULL;
	while (1) {
		fgets(input, sizeof input, stdin);
		for (p = input; p < (p + sizeof input); p++) {
			if (*p == '\n')
				break;
			/* liczba */
			if (*p >= '0' && *p <= '9') { 
				node *new;
				new = malloc(sizeof(node));
				new->val = *p - '0';
				while (*(p+1) >= '0' && *(p+1) <= '9') {
					new->val *= 10;
					new->val += *(p+1) - '0';
					p++;
				}
				new->next = head;
				head = new;
			}
			/* p */
			if (*p == 'p') {
				node *current = head;
				while (current != NULL) {
					printf("%d ", current->val);
					current = current->next;
				}
				printf("\n");
			}
			/* x */
			if (*p == 'x' && head != NULL) {
					node *next = head->next;
					free(head);
					head = next;
				}
			/* s */
			if (*p == 's') {
				node *temp = head;
     			node *temp_next = head->next;
				head->next = head->next->next;
				head = temp_next;
				head->next = temp;
			}
			/* + */
			if (*p == '+' && head->next != NULL) {
				node *sum = head->next;
				sum->val += head->val;
				free(head);
				head = sum;
			}
			/* r */
			if (*p == 'r') {
			    node *new_head;
				node *temp_prev;
				node *move = head->next;
				node *pre_head = head;
				head = move;
				if (pre_head->val > 1) {
					new_head = head->next;
					while (pre_head->val > 1) {
						move = move->next;
						pre_head->val--;
					}
					temp_prev = move;
					head->next = move->next;
					temp_prev->next = head;
					head = new_head;
				}
				free(pre_head);
			}
			/* q */
			if (*p == 'q')
				return 0;
		}
	}
}

