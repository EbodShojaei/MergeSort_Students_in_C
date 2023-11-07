# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

// Create a struct for the entity
// The entity will sort using merge sort
// 	Birth year
// 	Birth month
// 	Birth day
// 	Last name (alphabetical)
// 	First name (alphabetical)
// 	GPA
// 	TOEFL (none precedes)
// 	Domestic > International
//
// Merge sort
// 	e.g., [1 3 2 5 4 7 8 6]
// 	Split in half
// 		1325  4786
// 	Split again
// 		13  25  47  86
// 	Sort the elements
// 		13  25  47  68
// 	Merge to halves
// 		1325  4768
// 	Sort left
// 		1235
// 	Sort right
// 		4768
// 	Finally, insert in order
// 		12345678
//
// [1] Allow for sorting by just domestic students.
// [2] Allow for sorting by just international students.
// [3] Allow for sorting by all students.

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

const char *months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void callError() {
	printf("Error: Invalid input format.\n");
	exit(1);
}

// Recursive function to print the contents of a linked list
void printList(Student_t *head) {
	Student_t *current = head;
	while (current != NULL) {
		if (current->first_name != NULL) printf("%s ", current->first_name);
		if (current->last_name != NULL) printf("%s ", current->last_name);
		if (current->birth_month != NULL) printf("%s ", current->birth_month);
		if (current->birth_day != NULL) printf("%s ", current->birth_day);
		if (current->birth_year != NULL) printf("%s ", current->birth_year);
		if (current->gpa != NULL) printf("%s ", current->gpa);
		if (current->student_status != NULL) printf("%s ", current->student_status);
		if (current->toefl != NULL) printf("%s ", current->toefl);
		printf("\n");
		current = current->next;
	}
}

// Function to create a new node
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

// Function to append node to linked list
void appendList(Student_t **head, Student_t *next) {
	Student_t *current = *head;
	if (current == NULL) {
		*head = next;
		return;
	}

	while (current->next != NULL) current = current->next;
	current->next = next;
}

// Function to free linked list
void freeList(Student_t *head) {
	if (head == NULL) return;

	// Free other dynamically allocated
	freeList(head->next);
	free(head);
}

// Function to compare by year
int compareByYear(Student_t *a, Student_t *b) {
	if (atoi(a->birth_year) < atoi(b->birth_year)) return -1; // a is less than b
	if (atoi(a->birth_year) > atoi(b->birth_year)) return 1; // a is greater than b
	return 0; // a is equal to b
}

// Function to compare by month
int compareByMonth(Student_t *a, Student_t *b) {
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

// Function to compare by day
int compareByDay(Student_t *a, Student_t *b) {
	if (atoi(a->birth_day) < atoi(b->birth_day)) return -1; // a is less than b
	if (atoi(a->birth_day) > atoi(b->birth_day)) return 1; // a is greater than b
	return 0; // a is equal to b
}

// Function to compare by last name
int compareByLastName(Student_t *a, Student_t *b) {
	return strcmp(a->last_name, b->last_name);
}

// Function to compare by first name
int compareByFirstName(Student_t *a, Student_t *b) {
	return strcmp(a->first_name, b->first_name);
}

// Function to compare by GPA
int compareByGPA(Student_t *a, Student_t *b) {
	double gpa_a = atof(a->gpa);
	double gpa_b = atof(b->gpa);

	if (gpa_a < gpa_b) return -1; // a is less than b
	if (gpa_a > gpa_b) return 1; // a is greater than b
	return 0; // a is equal to b
}

// Function to compare by TOEFL
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

// Function to compare by student status
int compareByStatus(Student_t *a, Student_t *b) {
	return strcmp(a->student_status, b->student_status);
}

// Function to compare by all fields
int compareStudents(Student_t *a, Student_t *b) {
	int result;

	// Use each compare function in the given order until a difference is found
//	if ((result = compareByYear(a, b)) != 0) return result;
//	if ((result = compareByMonth(a, b)) != 0) return result;
//	if ((result = compareByDay(a, b)) != 0) return result;
//	if ((result = compareByLastName(a, b)) != 0) return result;
//	if ((result = compareByFirstName(a, b)) != 0) return result;
//	if ((result = compareByGPA(a, b)) != 0) return result;
//	if ((result = compareByTOEFL(a, b)) != 0) return result;
//	if ((result = compareByStatus(a, b)) != 0) return result;

	return 0; // a is equal to b
}

// Function to split a linked list into two halves
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

// Function to merge two linked lists
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

// Function to sort a linked list
void sortList(Student_t **head) {
	if (*head == NULL || (*head)->next == NULL) return;

	Student_t *left = NULL;
	Student_t *right = NULL;

	splitList(*head, &left, &right);

	sortList(&left);
	sortList(&right);

	*head = mergeList(left, right);
}

// Condition to sort by year of birth
// Condition to sort by month of birth
// Condition to sort by day of birth - Assume  
// Condition to sort by last name - Assume everyone has a last name. Output case same as input.
// Condition to sort by first name - Assume everyone has a first name. Output case same as input.
// Condition to sort by GPA - Assume everyone has a GPA up to 3 decimal places
// Condition to sort by TOEFL
// Condition to sort by student_status
// Function to merge sort
// Function to read

// Function to check if first or last name data (if not first/second str, then invalid format)
// Function to check if birth data (if <1950 or >2010, then invalid format)
// Function to check if GPA data (if >3 decimal places, then invalid format)
// Function to check if status data (
// Function to check if TOEFL data (if domestic student, then invalid format)
// 
// There are 6 strings per line.

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
	printf("Name is valid.\n\n");
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
	printf("Name is valid.\n\n");
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
		printf("%s\n", data);
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

	printf("Date is valid.\n\n");
}

void addGPA(char *gpa, Student_t *node) {
	printf("%s\n", gpa);
	char *ptr;
	double val = strtod(gpa, &ptr); // Convert string to double

	if (*ptr != '\0') callError(); // If there is a character, error
	if (val < 0.0 || val > 4.3) callError(); // If out of range, error
	if (strlen(gpa) > 5) callError(); // If more than 3 decimal places, error

	node->gpa = strdup(gpa);
	if (node->gpa == NULL) callError();
	printf("GPA is valid.\n\n");
}

void addStatus(char *status, Student_t *node) {
	if (status == NULL || (strcmp(status, "D") != 0 && strcmp(status, "I") != 0)) callError();

	node->student_status = strdup(status);
	if (node->student_status == NULL) callError();
	printf("Status is valid.\n\n");
}

void addTOEFL(char *toefl, Student_t *node) {
	if ((strcmp(node->student_status, "D") == 0) && (toefl != NULL)) callError();
	if ((strcmp(node->student_status, "I") == 0) && (toefl == NULL)) callError();

	if (toefl != NULL) {
		char *end_ptr;
		long val = strtol(toefl, &end_ptr, 10); // Convert string to int
	
		if (*end_ptr != '\0' || val < 0 || val > 120) callError(); // If out of range, error

		node->toefl = strdup(toefl);
		if (node->toefl == NULL) callError();
		printf("TOEFL is valid.\n\n");
	}
}

/**
 * Function to read in text. Checks conditions meeting fields.
 */ 
void readFile(FILE *file, Student_t *head) {
	Student_t *current = head;

	// Read in each line
	char *line = (char *) malloc(256 * sizeof(char));
	while (fgets(line, 256, file)) {
		int counter = 0; // Reset on new line. Up to 6 inputs
		char *delimiter = " \n";
		char *word = strtok(line, delimiter); // Gets the first string
		
		// Parse each string by space
		while (word != NULL) {
			if (counter > 6) callError();
			printf("Token: %s\n", word);
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
		appendList(&head, createNode());
		current = current->next;
	}
}

/**
 * ./<name of executable> <input file> <output file> <option>
 *
 * Example input: "Mary Jackson Feb-2-1990 4.0 I 60"
 *
 * Option is integer of 1, 2, or 3.
 *
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
	readFile(file, head);
	printList(head);
	sortList(&head);
	printList(head);



	return 0;
}
