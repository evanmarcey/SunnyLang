/*
 ============================================================================
 Name        : Sunny.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils/File_Utils.h"
#include "utils/String_Utils.h"
#include "utils/Math_Utils.h"
#include "utils/Misc_Utils.h"

#include "struct/Token.h"
#include "struct/Variable.h"
#include "struct/VariableStack.h"
#include "struct/CustomList.h"
#include "struct/ListItem.h"

#include "Exceptions.h"
#include "Tokenizer.h"
#include "GlobalVariables.h"

//#include "testing/TestingCustomLists.h"

static char * df = "./cmds.csv";
int SunnyLineNumber = 0;

int main(int argc, char* argv[]) {

	//clock_t start = clock(), diff;
	//printf("Test Results: %d\n",test_nested_CustomLists());
	int cmd_num_rows, cmd_num_fields;
	char *** cmds = load_csv(df,',',&cmd_num_fields,&cmd_num_rows);

	//handle incorrect command line issues;
	if (argc==1)
		CommandArgumentError("No file received from command line.",__LINE__,__FILE__);
	else if (argc > 2)
		CommandArgumentError("Too many commands received.",__LINE__,__FILE__);

	size_t file_name_length = strlen(argv[1]);
	if (strcmp(argv[1]+(file_name_length-3),".st\0")!=0)
		CommandArgumentError("File type not recognized. Use .st files.",__LINE__,__FILE__);

	//load the file
	char * s_file_name = malloc(sizeof(char)*file_name_length+1);
	s_file_name = argv[1];

	int sdata_num_rows;
	char ** s_data = load_file(s_file_name,&sdata_num_rows);

	//create our variable pointer arrays
	struct Variable ** variables = malloc(sizeof(struct Variable *)*sdata_num_rows);
	struct VariableStack * control_flow_stack = vs_create_stack(sdata_num_rows);

	int num_variables = 0;
	SunnyLineNumber = 0;

	//first, we tokenize the entire script
	struct Token *** token_array = malloc(sizeof(struct Token **)*sdata_num_rows);
	int token_array_lengths[sdata_num_rows];
	while (SunnyLineNumber < sdata_num_rows) {
		int num_tokens = 0;
		token_array[SunnyLineNumber] = tokenize_line(s_data[SunnyLineNumber],
				&num_tokens,
				cmds,
				cmd_num_rows,
				cmd_num_fields);

		token_array_lengths[SunnyLineNumber] = num_tokens;

		//fprintf(stdout,"Translated: ");
		//for (int j = 0; j < num_tokens; j++) {
		//	struct Token * t = token_array[i][j];
		//	fprintf(stdout,"%s ",get_token_value(t));
		//}
		//fprintf(stdout,"\n");
		SunnyLineNumber++;
	}

	//fprintf(stdout,"\n");
	SunnyLineNumber = 0;
	int depth = 0;
	//then we execute
	while (SunnyLineNumber < sdata_num_rows) {
		int line_number = SunnyLineNumber;
		eval_line(token_array[SunnyLineNumber],
				token_array_lengths[SunnyLineNumber],
				variables,
				&num_variables,
				control_flow_stack,
				&line_number,
				&depth,
				token_array,
				sdata_num_rows,
				token_array_lengths);
		if (line_number != SunnyLineNumber) {
			SunnyLineNumber = line_number;
		}
		else SunnyLineNumber++;

	}

	free(s_data);
	free(variables);
	/*
	diff = clock() - start;

	int msec = diff * 1000/CLOCKS_PER_SEC;
	fprintf(stdout,"\nTime taken %d seconds %d milliseconds", msec/1000, msec%1000);
	*/
	return 0;
}
