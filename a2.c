# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <ctype.h>

// Global error output
const char *error_output;

// Create a struct for the entity
typedef struct Student {
	char *first_name; // Alphabet
	char *last_name; // Alphabet
	char *birth_month; // Ranges from Jan to Dec
	char *birth_day; // Ranges from 1 to 31
	char *birth_year; // Ranges from 1950 to 2010
	char *gpa; // Ranges from 0.0 to 4.3
	char *status; // Either Domestic (D) or International (I)
	char *toefl; // Ranges from 0 to 120

	struct Student *next;
} Student_t;

// Create a wrapper struct to preserve order in StudentList_t
typedef struct ListNode {
	Student_t *student;
	struct ListNode *next;
} ListNode_t;

// Create a struct that orders the each of the lists by status
typedef struct StudentList {
	ListNode_t *head_d; // Head of domestic list
	ListNode_t *tail_d;
	ListNode_t *head_i; // Head of international list
	ListNode_t *tail_i;
	ListNode_t *head_a; // Head of all list
	ListNode_t *tail_a;
} StudentList_t;

// Months array
const char *months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/**
 * Function to call error.
 * Prints error message and exits.
 */
void callError(char *message) {
	printf("%s\n", message);
	printf("\n");
	if (error_output == NULL) exit(1);
	FILE *file = fopen(error_output, "w");
	fprintf(file, "%s\n", message);
	// fprintf(file, "\n");
	fclose(file);
	exit(1);
}

/**
 * Function to create a node.
 * Dynamically allocates memory for the node.
 * If the node is NULL, then error.
 */
Student_t *createNode() {
	Student_t *node = (Student_t *) malloc(sizeof(Student_t));
	if (node == NULL) callError("Error: Memory could not be allocated.");

	node->first_name = NULL;
	node->last_name = NULL;
	node->birth_month = NULL;
	node->birth_day = NULL;
	node->birth_year = NULL;
	node->gpa = NULL;
	node->status = NULL;
	node->toefl = NULL;
	node->next = NULL;

	return node;
}

/**
 * Function to wrap a Student_t node in a ListNode_t node.
 * If the head is NULL, then the head is the node.
 */
void appendToList(ListNode_t **head, ListNode_t **tail, Student_t *student) {
	ListNode_t *node = (ListNode_t *) malloc(sizeof(ListNode_t));
	if (node == NULL) callError("Error: Memory could not be allocated.");
	node->student = student;
	node->next = NULL;

	if (*head == NULL) *head = node;
	else (*tail)->next = node;
	*tail = node;
}

/**
 * Function to append a node to the end of the linked list.
 */
void appendList(StudentList_t *list, Student_t *new_node) {
	if (list == NULL || new_node == NULL) callError("Error: NULL argument.");

	// Append to all list
	appendToList(&list->head_a, &list->tail_a, new_node);

	// Append to domestic or international list
	if (new_node->status != NULL) {
		switch (new_node->status[0]) {
			case 'D': appendToList(&list->head_d, &list->tail_d, new_node); break;
			case 'I': appendToList(&list->head_i, &list->tail_i, new_node); break;
			default: callError("Error: Invalid status.");
		}
	}
}

/**
 * Function to free the linked list.
 * Frees by all fields.
 */
void freeList(ListNode_t *node) {
	while (node != NULL) {
		ListNode_t *temp = node;
		node = node->next;

		// Free dynamically allocated strings within the node
		if (temp->student->first_name != NULL) free(temp->student->first_name);
		if (temp->student->last_name != NULL) free(temp->student->last_name);
		if (temp->student->birth_month != NULL) free(temp->student->birth_month);
		if (temp->student->birth_day != NULL) free(temp->student->birth_day);
		if (temp->student->birth_year != NULL) free(temp->student->birth_year);
		if (temp->student->gpa != NULL) free(temp->student->gpa);
		if (temp->student->status != NULL) free(temp->student->status);
		if (temp->student->toefl != NULL) free(temp->student->toefl);
		
		free(temp->student);
		free(temp);
	}
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
	if (a->toefl == NULL && b->toefl != NULL) return -1; // a is domestic, b is international
	if (a->toefl != NULL && b->toefl == NULL) return 1; // a is international, b is domestic
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
	if (a->status == NULL && b->status != NULL) return 1;
	if (a->status != NULL && b->status == NULL) return -1;
	if (a->status == NULL && b->status == NULL) return 0;

	return strcmp(a->status, b->status);
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
void splitList(ListNode_t *head, ListNode_t **left, ListNode_t **right) {
	if (head == NULL || head->next == NULL) {
		*left = head;
		*right = NULL;
		return;
	}

	ListNode_t *slow = head;
	ListNode_t *fast = head->next;

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
ListNode_t *mergeList(ListNode_t *left, ListNode_t *right) {
	ListNode_t *result = NULL;

	if (left == NULL) return right;
	if (right == NULL) return left;

	int compare = compareStudents(left->student, right->student);
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
void sortList(ListNode_t **head) {
	if (*head == NULL || (*head)->next == NULL) return;

	ListNode_t *left = NULL;
	ListNode_t *right = NULL;

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
	char *error_message = "Error: Invalid first name.";

	// If the name does not contain letters, error.
	for (int i = 0; i < strlen(name); i++)
		if (!isalpha(name[i])) callError(error_message);

	node->first_name = strdup(name);
	if (node->first_name == NULL) callError(error_message);
}

/**
 * Function to check if valid name.
 * Valid name contains letters.
 * Checks last name.
 */
void addLastName(char *name, Student_t *node) {
	char *error_message = "Error: Invalid last name.";

	// If the name does not contain letters, error.
	for (int i = 0; i < strlen(name); i++)
		if (!isalpha(name[i])) callError(error_message);

	node->last_name = strdup(name);
	if (node->last_name == NULL) callError(error_message);
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
	char *ptr;
	char *data = strtok_r(date, delimiter, &ptr); 
	char *end_ptr;

	while (data != NULL) {
		counter++;
		switch (counter) {
			case 1: // Month
				// Check if equals to one of the months
				for (int i = 0; i < 12; i++)
					if (strcmp(data, months[i]) == 0) break;
					else if (i == 11) callError("Error: Invalid month.");
				node->birth_month = strdup(data);
				if (node->birth_month == NULL) callError("Error: Invalid month.");
				break;
			case 2: // Day
				// Check if number and not other characters
				if (data[0] == '0') callError("Error: Invalid day."); // If leading zero, error
				long day = strtol(data, &end_ptr, 10); // Convert string to int
				
				// Check if number is between 1 and 31
				if (*end_ptr != '\0' || day < 1 || day > 31) callError("Error: Invalid day.");
				node->birth_day = strdup(data);
				if (node->birth_day == NULL) callError("Error: Invalid day.");
				break;
			case 3: // Year
				// Check if number and not other characters
				if (data[0] == '0') callError("Error: Invalid year."); // If leading zero, error
				long year = strtol(data, &end_ptr, 10); // Convert string to int
				
				// Check if number is between 1950 and 2010
				if (*end_ptr != '\0' || year < 1950 || year > 2010) callError("Error: Invalid year.");
				node->birth_year = strdup(data);
				if (node->birth_year == NULL) callError("Error: Invalid year.");
				break;
			default:
				callError("Error: Invalid date format.");
		}
		data = strtok_r(NULL, delimiter, &ptr); // Gets the next string
	}
}

/**
 * Function to check if valid GPA.
 */
void addGPA(char *gpa, Student_t *node) {
	char *error_message = "Error: Invalid GPA.";
	if (gpa[0] == '0' && gpa[1] != '.') callError(error_message); // If leading zero, error

	char *ptr;
	double val = strtod(gpa, &ptr); // Convert string to double

	if (*ptr != '\0') callError(error_message); // If there is a character, error
	if (val < 0.0 || val > 4.3) callError(error_message); // If out of range, error
	if (strlen(gpa) > 5) callError(error_message); // If more than 3 decimal places, error

	node->gpa = strdup(gpa);
	if (node->gpa == NULL) callError(error_message);
}

/**
 * Function to check if valid status.
 * Valid status is either D or I.
 */
void addStatus(char *status, Student_t *node) {
	char *error_message = "Error: Invalid status.";
	if (status == NULL || (strcmp(status, "D") != 0 && strcmp(status, "I") != 0)) callError(error_message);

	node->status = strdup(status);
	if (node->status == NULL) callError(error_message);
}

/**
 * Function to check if valid TOEFL.
 * Valid TOEFL is between 0 and 120.
 */
void addTOEFL(char *toefl, Student_t *node) {
	char *error_message = "Error: Invalid TOEFL.";
	
	if ((strcmp(node->status, "D") == 0) && (toefl != NULL)) callError(error_message);
	if ((strcmp(node->status, "I") == 0) && (toefl == NULL)) callError(error_message);

	if (toefl != NULL) {
		if (toefl[0] == '0' && toefl[1] == '0') callError(error_message);

		char *end_ptr;
		long val = strtol(toefl, &end_ptr, 10); // Convert string to int
	
		if (*end_ptr != '\0' || val < 0 || val > 120) callError(error_message); // If out of range, error

		node->toefl = strdup(toefl);
		if (node->toefl == NULL) callError(error_message);
	}
}

/**
 * Function to process word into Student struct.
 */
void processWord(char *word, Student_t *current, int word_count) {
	switch (word_count) {
		case 1: addFirstName(word, current); break;
		case 2: addLastName(word, current); break;
		case 3: addDate(word, current); break;
		case 4: addGPA(word, current); break;
		case 5: addStatus(word, current); break;
		case 6: addTOEFL(word, current); break;
		default: callError("Error: Incorrect input format.");
	}
}

/**
 * Function to read text from input file. 
 */ 
void readFile(FILE *input, StudentList_t *list, const int option, char *encoding) {
	if (input == NULL) callError("Error: Could not read file."); // Error handle reading file

	Student_t *current = createNode();
	int size = 20;
	char *buffer = (char *) malloc(sizeof(char) * size);
	if (buffer == NULL) callError("Error: Memory could not be allocated.");

	char c;
	char last_char;
	char *word = buffer; // Pointer to buffer
	int characters = 0;
	int word_count = 0;
	int word_length = 0;
	int space_count = 0;
	bool in_word = false;

	while ((c = fgetc(input)) != EOF) {
		if (ferror(input)) { // Error handle reading file
			free(buffer);
			fclose(input);
			callError("Error: Could not read file.");
		}
		if (space_count > 1) { // Error handle consecutive spaces
			free(buffer);
			fclose(input);
			callError("Error: Consecutive spaces is invalid format.");
		}
		if (word_count > 6) { // Error handle too many words
			free(buffer);
			fclose(input);
			callError("Error: Too many fields."); 
		}
		if (word_length >= (size - 1)) { // Reallocate memory if word is too long
			size *= 2;
			char *temp = (char *) realloc(buffer, sizeof(char) * size);
			if (temp == NULL) {
				free(buffer);
				fclose(input);
				callError("Error: Memory could not be allocated.");
			}
			buffer = temp;
			word = buffer + word_length; // Continue building string from last char
		}

		if (!isspace(c)) {
			if (!in_word) { // Start of word 
				word_count++;
				space_count = 0;
				in_word = true;
			}
			*word++ = c;
			word_length++;
		} else if (isspace(c)) {
			if (c != '\r' && c != '\n' && word_count == 0) callError("Error: Leading spaces is invalid format."); // Error handle leading spaces
		
			if (in_word) { // End of word
				*word = '\0';
				processWord(buffer, current, word_count); // Process word	
				word = buffer; // Reset word
				memset(buffer, 0, 20); // Reset buffer
				word_length = 0;
				in_word = false;
			}
			if (c == '\r' ) {
				*encoding = 'W';
				char next_char = fgetc(input); // Peek next character
				if (next_char != '\n') callError("Error: Carriage return is invalid format.");
			}
			space_count++;
		}
		// Reset word count if end of line
		if ((c == '\r' || c == '\n') && space_count != 0) {
			// Error handle empty line
			// Only last line can be empty
			if (word_count == 0) {
				last_char = (char) c;
				char next_char = fgetc(input); // Peek next character
				if (next_char == EOF && characters != 0) break;
				else callError("Error: Empty line is invalid format.");
			}

			// Error handle trailing spaces
			if (space_count > 1) callError("Error: Trailing spaces is invalid format.");

			// Append Student to linked list
			appendList(list, current);
			current = createNode();

			// Reset counts for next line
			word_count = 0;
			space_count = 0;
		}
		characters++;
	} // End of while loop
	free(buffer);
	if (last_char != 0 && last_char != '\r' && last_char != '\n') callError("Error: Last line is invalid format.");
}

/**
 * Function to write text to output file.
 * Writes by all fields.
 */
void writeFile(FILE *output, ListNode_t *head, const char *encoding) {
	ListNode_t *current = head;
	while (current != NULL) {
		Student_t *student = current->student;
		if (student->first_name != NULL) fprintf(output, "%s ", student->first_name);
		if (student->last_name != NULL) fprintf(output, "%s ", student->last_name);
		if (student->birth_month != NULL) fprintf(output, "%s-", student->birth_month);
		if (student->birth_day != NULL) fprintf(output, "%s-", student->birth_day);
		if (student->birth_year != NULL) fprintf(output, "%s ", student->birth_year);
		if (student->gpa != NULL) fprintf(output, "%s ", student->gpa);
		if (student->status != NULL && *student->status == 'D') fprintf(output, "%s", student->status);
		else if (student->status != NULL && *student->status == 'I') fprintf(output, "%s ", student->status);
		if (student->toefl != NULL) fprintf(output, "%s", student->toefl);
		if (*encoding == 'U') fprintf(output, "\n");
		else if (*encoding == 'W') fprintf(output, "\r\n");
		current = current->next;
	}
	// Output file must end with a new line
	// fprintf(output, "\n");

	// Close the output file
	fclose(output);

	printf("Successfully wrote to output file.\n");
	printf("\n");
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
	char *ANum = "A01351112";
	FILE *outputFile = fopen(ANum, "w");
	if (outputFile == NULL) {
		printf("Error: Failed to create output file.\n");
		return 1;
	}
	fclose(outputFile);

	// Check if number of arguments is valid. Then get inputs.
	if (argc != 4) {
		printf("Usage %s <input_file> <output_file> <option>\n", argv[0]);
		callError("Error: Invalid number of arguments.");
	}
	const char *input_name = argv[1]; // Input file name
	const char *output_name = argv[2]; // Output file name
	error_output = output_name; // Set global error output
	
	// Open input file
	FILE *file = fopen(input_name, "r");
	if (file == NULL) callError("Error: Input file not found.");
	fseek(file, 0, SEEK_SET); // Ensure cursor at start of file

	// Check if option is valid
	const int option = atoi(argv[3]);
	if (option < 1 || option > 3) {
		printf("Usage %s <input_file> <output_file> <option>\n", argv[0]);
		callError("Error: Invalid option.");
	}

	// Setup linked list
	ListNode_t *head = NULL;
	StudentList_t *list = (StudentList_t *) malloc(sizeof(StudentList_t));
	if (list == NULL) callError("Error: Memory could not be allocated.");

	// Read from input file
	char encoding = 'U'; // Default encoding is UNIX. Function changes to Windows if needed.
	readFile(file, list, option, &encoding);
	switch (option) {
		case 1: head = list->head_d; break; // Domestic
		case 2: head = list->head_i; break; // International
		case 3: head = list->head_a; break; // All
	}
	sortList(&head);
	fclose(file);

	// Write to output file
	file = fopen(output_name, "w");
	if (file == NULL) {
		callError("Error: Output file could not open.");
	}
	writeFile(file, head, &encoding);

	// Clean up
	if (list->head_a != NULL) freeList(list->head_a);
	free(list);

	return 0;
}
