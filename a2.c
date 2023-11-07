# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

// Create a struct for the entity
typedef struct Student {
	char *first_name; // Alphabet
	char *last_name; // Alphabet
	char *birth_month; // Ranges from Jan to Dec
	char *birth_day; // Ranges from 1 to 31
	char *birth_year; // Ranges from 1950 to 2010
	char *gpa; // Ranges from 0.0 to 4.3
	char *student_status; // Either Domestic (D) or International (I)
	char *toefl; // Ranges from 0 to 120

	struct Student *next;
} Student_t;

// Months array
const char *months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/**
 * Function to call error.
 * Prints error message and exits.
 */
void callError() {
	printf("Error: Invalid input format.\n");
	exit(1);
}

/**
 * Function to print the linked list.
 * Prints by all fields.
 */
void printList(Student_t *head) {
	Student_t *current = head;
	while (current != NULL) {
		if (current->first_name != NULL) printf("%s ", current->first_name);
		if (current->last_name != NULL) printf("%s ", current->last_name);
		if (current->birth_month != NULL) printf("%s-", current->birth_month);
		if (current->birth_day != NULL) printf("%s-", current->birth_day);
		if (current->birth_year != NULL) printf("%s ", current->birth_year);
		if (current->gpa != NULL) printf("%s ", current->gpa);
		if (current->student_status != NULL) printf("%s ", current->student_status);
		if (current->toefl != NULL) printf("%s ", current->toefl);
		printf("\n");
		current = current->next;
	}
}

/**
 * Function to create a node.
 * Dynamically allocates memory for the node.
 * If the node is NULL, then error.
 */
Student_t *createNode() {
	Student_t *node = (Student_t *) malloc(sizeof(Student_t));
	if (node == NULL) callError();

	node->first_name = NULL;
	node->last_name = NULL;
	node->birth_month = NULL;
	node->birth_day = NULL;
	node->birth_year = NULL;
	node->gpa = NULL;
	node->student_status = NULL;
	node->toefl = NULL;
	node->next = NULL;

	return node;
}

/**
 * Function to append a node to the end of the linked list.
 * If the head is NULL, then the head is the node.
 */
void appendList(Student_t **head, Student_t *next) {
	Student_t *current = *head;
	if (current == NULL) {
		*head = next;
		return;
	}

	while (current->next != NULL) current = current->next;
	current->next = next;
}

/**
 * Function to free the linked list.
 * Frees by all fields.
 */
void freeList(Student_t *head) {
	if (head == NULL) return;

	// Free other dynamically allocated
	freeList(head->next);
	free(head);
}

/**
 * Function to compare by year.
 * NULL precedes non-NULL.
 */
int compareByYear(Student_t *a, Student_t *b) {
	if (a->birth_year == NULL && b->birth_year != NULL) return 1;
	if (a->birth_year != NULL && b->birth_year == NULL) return -1;
	if (a->birth_year == NULL && b->birth_year == NULL) return 0;

	if (atoi(a->birth_year) < atoi(b->birth_year)) return -1; // a is less than b
	if (atoi(a->birth_year) > atoi(b->birth_year)) return 1; // a is greater than b
	return 0; // a is equal to b
}

/**
 * Function to compare by month.
 */
int compareByMonth(Student_t *a, Student_t *b) {
	if (a->birth_month == NULL && b->birth_month != NULL) return 1;
	if (a->birth_month != NULL && b->birth_month == NULL) return -1;
	if (a->birth_month == NULL && b->birth_month == NULL) return 0;

	// Get the index of the month from the months array
	int a_index = 0;
	int b_index = 0;

	for (int i = 0; i < 12; i++) {
		if (strcmp(a->birth_month, months[i]) == 0) a_index = i;
		if (strcmp(b->birth_month, months[i]) == 0) b_index = i;
	}

	if (a_index < b_index) return -1; // a is less than b
	if (a_index > b_index) return 1; // a is greater than b
	return 0; // a is equal to b
}

/**
 * Function to compare by day.
 * NULL precedes non-NULL.
 */
int compareByDay(Student_t *a, Student_t *b) {
	if (a->birth_day == NULL && b->birth_day != NULL) return 1;
	if (a->birth_day != NULL && b->birth_day == NULL) return -1;
	if (a->birth_day == NULL && b->birth_day == NULL) return 0;

	if (atoi(a->birth_day) < atoi(b->birth_day)) return -1; // a is less than b
	if (atoi(a->birth_day) > atoi(b->birth_day)) return 1; // a is greater than b
	return 0; // a is equal to b
}

/**
 * Function to compare by last name.
 * NULL precedes non-NULL.
 */
int compareByLastName(Student_t *a, Student_t *b) {
	if (a->last_name == NULL && b->last_name != NULL) return 1;
	if (a->last_name != NULL && b->last_name == NULL) return -1;
	if (a->last_name == NULL && b->last_name == NULL) return 0;

	return strcmp(a->last_name, b->last_name);
}

/**
 * Function to compare by first name.
 * NULL precedes non-NULL.
 */
int compareByFirstName(Student_t *a, Student_t *b) {
	if (a->first_name == NULL && b->first_name != NULL) return 1;
	if (a->first_name != NULL && b->first_name == NULL) return -1;
	if (a->first_name == NULL && b->first_name == NULL) return 0;

	return strcmp(a->first_name, b->first_name);
}

/**
 * Function to compare by GPA.
 * NULL precedes non-NULL.
 */
int compareByGPA(Student_t *a, Student_t *b) {
	if (a->gpa == NULL && b->gpa != NULL) return 1;
	if (a->gpa != NULL && b->gpa == NULL) return -1;
	if (a->gpa == NULL && b->gpa == NULL) return 0;

	double gpa_a = atof(a->gpa);
	double gpa_b = atof(b->gpa);

	if (gpa_a < gpa_b) return -1; // a is less than b
	if (gpa_a > gpa_b) return 1; // a is greater than b
	return 0; // a is equal to b
}

/**
 * Function to compare by TOEFL.
 * Domestic precedes international.
 */
int compareByTOEFL(Student_t *a, Student_t *b) {
	// If no TOEFL, then domestic
	if (a->toefl == NULL && b->toefl != NULL) return 1; // a is domestic, b is international
	if (a->toefl != NULL && b->toefl == NULL) return -1; // a is international, b is domestic
	if (a->toefl == NULL && b->toefl == NULL) return 0; // Both are domestic
	
	// Both have TOEFL, so compare
	int toefl_a = atoi(a->toefl);
	int toefl_b = atoi(b->toefl);

	if (toefl_a < toefl_b) return -1; // a is less than b
	if (toefl_a > toefl_b) return 1; // a is greater than b
	return 0; // a is equal to b
}

/**
 * Function to compare by status.
 * Domestic precedes international.
 */
int compareByStatus(Student_t *a, Student_t *b) {
	if (a->student_status == NULL && b->student_status != NULL) return 1;
	if (a->student_status != NULL && b->student_status == NULL) return -1;
	if (a->student_status == NULL && b->student_status == NULL) return 0;

	return strcmp(a->student_status, b->student_status);
}

/**
 * Function to compare two students.
 * Compares by all fields.
 */
int compareStudents(Student_t *a, Student_t *b) {
	int result;

	// Use each compare function in the given order until a difference is found
	if ((result = compareByYear(a, b)) != 0) return result;
	if ((result = compareByMonth(a, b)) != 0) return result;
	if ((result = compareByDay(a, b)) != 0) return result;
	if ((result = compareByLastName(a, b)) != 0) return result;
	if ((result = compareByFirstName(a, b)) != 0) return result;
	if ((result = compareByGPA(a, b)) != 0) return result;
	if ((result = compareByTOEFL(a, b)) != 0) return result;
	if ((result = compareByStatus(a, b)) != 0) return result;

	return 0; // a is equal to b
}

/**
 * Function to split a linked list into two halves.
 * Splits by all fields.
 */
void splitList(Student_t *head, Student_t **left, Student_t **right) {
	if (head == NULL || head->next == NULL) {
		*left = head;
		*right = NULL;
		return;
	}

	Student_t *slow = head;
	Student_t *fast = head->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*left = head;
	*right = slow->next;
	slow->next = NULL;
}

/**
 * Function to merge two linked lists.
 * Merges by all fields.
 */
Student_t *mergeList(Student_t *left, Student_t *right) {
	Student_t *result = NULL;

	if (left == NULL) return right;
	if (right == NULL) return left;

	int compare = compareStudents(left, right);
	if (compare <= 0) {
		result = left;
		result->next = mergeList(left->next, right);
	} else {
		result = right;
		result->next = mergeList(left, right->next);
	}

	return result;
}

/**
 * Function to sort a linked list using merge sort.
 * Sorts by all fields.
 */
void sortList(Student_t **head) {
	if (*head == NULL || (*head)->next == NULL) return;

	Student_t *left = NULL;
	Student_t *right = NULL;

	splitList(*head, &left, &right);

	sortList(&left);
	sortList(&right);

	*head = mergeList(left, right);
}

/**
 * Function to check if valid name.
 * Valid name contains letters.
 * Checks first last name.
 */
void addFirstName(char *name, Student_t *node) {
	// If the name does not contain letters, error.
	for (int i = 0; i < strlen(name); i++)
		if (!isalpha(name[i])) callError();

	node->first_name = strdup(name);
	if (node->first_name == NULL) callError();
	//printf("Name is valid.\n\n");
}

/**
 * Function to check if valid name.
 * Valid name contains letters.
 * Checks last name.
 */
void addLastName(char *name, Student_t *node) {
	// If the name does not contain letters, error.
	for (int i = 0; i < strlen(name); i++)
		if (!isalpha(name[i])) callError();

	node->last_name = strdup(name);
	if (node->last_name == NULL) callError();
	//printf("Name is valid.\n\n");
}

/**
 * Function to check if valid date.
 * Valid date contains numbers.
 * Checks month, day, and year.
 */
void addDate(char *date, Student_t *node) {
	// Delimit each dash e.g., Month-Day-Year
	int counter = 0;
	char *delimiter = "-";
	char *data = strtok_r(date, delimiter, &date); 

	while (data != NULL) {
		//printf("%s\n", data);
		counter++;
		
		switch (counter) {
			case 1: // Month
				// Check if equals to one of the months
				for (int i = 0; i < 12; i++)
					if (strcmp(data, months[i]) == 0) break;
					else if (i == 11) callError();
				node->birth_month = strdup(data);
				if (node->birth_month == NULL) callError();
				break;
			case 2: // Day
				// Check if number is between 1 and 31
				if (atoi(data) < 1 || atoi(data) > 31) callError();
				node->birth_day = strdup(data);
				if (node->birth_day == NULL) callError();
				break;
			case 3: // Year
				// Check if number is between 1950 and 2010
				if (atoi(data) < 1950 || atoi(data) > 2010) callError();
				node->birth_year = strdup(data);
				if (node->birth_year == NULL) callError();
				break;
			default:
				callError();
		}
		data = strtok_r(NULL, delimiter, &date); // Gets the next string
	}

	//printf("Date is valid.\n\n");
}

/**
 * Function to check if valid GPA.
 */
void addGPA(char *gpa, Student_t *node) {
	//printf("%s\n", gpa);
	char *ptr;
	double val = strtod(gpa, &ptr); // Convert string to double

	if (*ptr != '\0') callError(); // If there is a character, error
	if (val < 0.0 || val > 4.3) callError(); // If out of range, error
	if (strlen(gpa) > 5) callError(); // If more than 3 decimal places, error

	node->gpa = strdup(gpa);
	if (node->gpa == NULL) callError();
	//printf("GPA is valid.\n\n");
}

/**
 * Function to check if valid status.
 * Valid status is either D or I.
 */
void addStatus(char *status, Student_t *node) {
	if (status == NULL || (strcmp(status, "D") != 0 && strcmp(status, "I") != 0)) callError();

	node->student_status = strdup(status);
	if (node->student_status == NULL) callError();
	//printf("Status is valid.\n\n");
}

/**
 * Function to check if valid TOEFL.
 * Valid TOEFL is between 0 and 120.
 */
void addTOEFL(char *toefl, Student_t *node) {
	if ((strcmp(node->student_status, "D") == 0) && (toefl != NULL)) callError();
	if ((strcmp(node->student_status, "I") == 0) && (toefl == NULL)) callError();

	if (toefl != NULL) {
		char *end_ptr;
		long val = strtol(toefl, &end_ptr, 10); // Convert string to int
	
		if (*end_ptr != '\0' || val < 0 || val > 120) callError(); // If out of range, error

		node->toefl = strdup(toefl);
		if (node->toefl == NULL) callError();
		//printf("TOEFL is valid.\n\n");
	}
}

/**
 * Function to read text from input file. 
 * Checks conditions meeting fields.
 */ 
void readFile(FILE *input, Student_t *head, const int option) {
	Student_t *current = head;

	// Read in each line
	char *line = (char *) malloc(256 * sizeof(char));
	while (fgets(line, 256, input)) {
		int counter = 0; // Reset on new line. Up to 6 inputs
		char *delimiter = " \n";
		char *word = strtok(line, delimiter); // Gets the first string
		
		// Parse each string by space
		while (word != NULL) {
			if (counter > 6) callError();
			//printf("Token: %s\n", word);
			counter++;

			switch (counter) {
				case 1: addFirstName(word, current); break;
				case 2: addLastName(word, current); break;
				case 3: addDate(word, current); break;
				case 4: addGPA(word, current); break;
				case 5: addStatus(word, current); break;
				case 6: addTOEFL(word, current); break;
				default: callError();
			}
			word = strtok(NULL, delimiter); // Gets the next string
		}
		switch (option) {
			case 1: // Domestic
				if (strcmp(current->student_status, "D") == 0) {
					appendList(&head, createNode());
					current = current->next;
				} else {
					freeList(current);
					current = createNode();
				}
				break;
			case 2: // International
				if (strcmp(current->student_status, "I") == 0) { 
					appendList(&head, createNode());
					current = current->next;
				} else {
					freeList(current);
					current = createNode();
				}
				break;
			case 3: // All
				appendList(&head, createNode());
				current = current->next;
				break;
		}
	}
}

/**
 * Function to write text to output file.
 * Writes by all fields.
 */
void writeFile(FILE *output, Student_t *head) {
	Student_t *current = head;
	while (current != NULL) {
		if (current->first_name != NULL) fprintf(output, "%s ", current->first_name);
		if (current->last_name != NULL) fprintf(output, "%s ", current->last_name);
		if (current->birth_month != NULL) fprintf(output, "%s-", current->birth_month);
		if (current->birth_day != NULL) fprintf(output, "%s-", current->birth_day);
		if (current->birth_year != NULL) fprintf(output, "%s ", current->birth_year);
		if (current->gpa != NULL) fprintf(output, "%s ", current->gpa);
		if (current->student_status != NULL) fprintf(output, "%s ", current->student_status);
		if (current->toefl != NULL) fprintf(output, "%s ", current->toefl);
		if (current->next != NULL) fprintf(output, "\n");
		current = current->next;
	}

	// Close the output file
	fclose(output);

	printf("Successfully wrote to output file.\n");
}

/**
 * Driver program.
 *
 * Usage:
 * 		./<name of executable> <input file> <output file> <option>
 *
 * Options as follows:
 * 		[1] Allow for sorting by just domestic students.
 * 		[2] Allow for sorting by just international students.
 * 		[3] Allow for sorting by all students.
 *
 * Example input: 
 * 		"Mary Jackson Feb-2-1990 4.0 I 60"
 */
int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Error: Usage %s <input_file> <output_file> <option>\n", argv[0]);
		return 1;
	}

	const char *input_name = argv[1];
	FILE *file = fopen(input_name, "r");

	if (file == NULL) {
		printf("Error: File not found.\n");
		return 1;
	}
	Student_t *head = createNode();

	const int option = atoi(argv[3]);
	if (option < 1 || option > 3) {
		printf("Error: Usage %s <input_file> <output_file> <option>\n", argv[0]);
		return 1;
	}
	readFile(file, head, option);
//	printList(head);
	sortList(&head);
//	printList(head);

	fclose(file);

	const char *output_name = argv[2];
	file = fopen(output_name, "w");
	
	if (file == NULL) {
		printf("Error: File could not open.\n");
		return 1;
	}
	writeFile(file, head);

	return 0;
}
