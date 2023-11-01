# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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
	char[] first_name; // Alphabet
	char[] last_name; // Alphabet
	char[] birth_month; // Ranges from Jan to Dec
	char[] birth_day; // Ranges from 1 to 31
	char[] birth_year; // Ranges from 1950 to 2010
	char[] gpa; // Ranges from 0.0 to 4.3
	char[] student_status; // Either Domestic (D) or International (I)
	char[] toefl; // Ranges from 0 to 120

	Student *next;
} Student_t;



// Condition to sort by year of birth
// Condition to sort by month of birth
// Condition to sort by day of birth - Assume  
// Condition to sort by last name - Assume everyone has a last name. Output case same as input.
// Condition to sort by first name - Assume everyone has a first name. Output case same as input.
// Condition to sort by GPA - Assume everyone has a GPA up to 3 decimal places
// Condition to sort by TOEFL - Assume every
// Condition to sort by student_status
// Function to merge sort
// Function to read

// Function to check if name
// Function to check if bi

/**
 * Read in text. Checks conditions meeting fields.
 */ 
void readFile(FILE *file, Student_t *node) {
	// Use strtok for next string of file stream
	// Is this a name?
	char[] *line = (char *) malloc( * sizeof(char));
	while (fgets(line, 256, file) != EOF) {
		char[] *word = strtok(line, " ");
	
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
int main(int argc, char argc[]) {
	if (argc != 4) {
		printf("Error: Usage %s <input_file> <output_file> <option>", argv[0]);
		return 1;
	}

	const char *input_name = argv[1];
	FILE *file = fopen(input_name, "r");

	if (file == NULL) {
		printf("Error: File not found."\n);
		return 1;
	}

	return 0;
}
