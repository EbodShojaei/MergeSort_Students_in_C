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

void callError() {
	printf("Error: Invalid input format.\n");
	exit(1);
}

/**
 * Function to check if valid name.
 * Valid name contains letters.
 * Checks first and last name.
 */
void checkName(char *name) {
	// If the name does not contain letters, error.
	for (int i = 0; i < strlen(name); i++)
		if (!isalpha(name[i])) callError();

	printf("Name is valid.\n\n");
}

/**
 * Function to check if valid date.
 * Valid date contains numbers.
 * Checks month, day, and year.
 */
void checkDate(char *date) {
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
				break;
			case 2: // Day
				// Check if number is between 1 and 31
				if (atoi(data) < 1 || atoi(data) > 31) callError();
				break;
			case 3: // Year
				// Check if number is between 1950 and 2010
				if (atoi(data) < 1950 || atoi(data) > 2010) callError();
				break;
			default:
				callError();
		}
		data = strtok_r(NULL, delimiter, &date); // Gets the next string
	}

	printf("Date is valid.\n\n");
}

void checkGPA(char *gpa) {
	printf("%s\n", gpa);
	char *ptr;
	double val = strtod(gpa, &ptr); // Convert string to double

	if (*ptr != '\0') callError(); // If there is a character, error
	if (val < 0.0 || val > 4.3) callError(); // If out of range, error
	if (strlen(gpa) > 4) callError(); // If more than 3 decimal places, error

	printf("GPA is valid.\n\n");
}

void checkStatus(char *status) {
	if (strcmp(status, "D") != 0 && strcmp(status, "I") != 0) callError();

	printf("Status is valid.\n\n");
}

void checkTOEFL(char *toefl) {
	char *ptr;
	int val = atoi(toefl); // Convert string to int

	if (val < 0 || val > 120) callError(); // If out of range, error

	printf("TOEFL is valid.\n\n");
}

/**
 * Function to read in text. Checks conditions meeting fields.
 */ 
void readFile(FILE *file) {
	// Use strtok for next string of file stream
	// Is this a name?
	char *line = (char *) malloc(256 * sizeof(char));
	while (fgets(line, 256, file)) {
		int counter = 0; // Reset on new line. Up to 6 inputs
		char *delimiter = " ";
		char *word = strtok(line, delimiter); // Gets the first string
		
		while (word != NULL) {
			printf("Token: %s\n", word);
			counter++;

			// checkString(word);
			switch (counter) {
				case 1:
					checkName(word);
					break;
				case 2:
					checkName(word);
					break;
				case 3:
					checkDate(word);
					break;
				case 4:
					checkGPA(word);
					break;
				case 5:
					checkStatus(word);
					break;
				case 6:
					checkTOEFL(word);
					break;
				default:
					callError();
			}

			word = strtok(NULL, delimiter); // Gets the next string
		}
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

	readFile(file);

	return 0;
}
