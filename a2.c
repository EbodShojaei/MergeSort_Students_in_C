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
// Allow for sorting by just domestic students.
// Allow for sorting by just international students.
// Allow for sorting by all students.

typedef struct student {
	char[] first_name; // Alphabet
	char[] last_name; // Alphabet
	char[] birth_month; // Ranges from Jan to Dec
	char[] birth_day; // Ranges from 1 to 31
	char[] birth_year; // Ranges from 1950 to 2010
	char[] gpa; // Ranges from 0.0 to 4.3
	char[] student_status; // Either Domestic or International
	char[] toefl; // Ranges from 0 to 120

	student *next;
} student_t;

// Condition to sort by year of birth
// Condition to sort by month of birth
// Condition to sort by day of birth
// Condition to sort by last name
// Condition to sort by first name
// Condition to sort by GPA
// Condition to sort by TOEFL
// Condition to sort by student_status

int main() {
	
	return 0;
}
