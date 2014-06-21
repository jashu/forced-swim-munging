Forced Swim Munging
=====================

The program "FST.exe" takes a file with 5 minutes of raw forced swim data **WITHOUT HEADERS**
or any other extraneous info, and returns a minute-by-minute summation of each behavior.

Each line must be in the following format, separated by white space:

	subject	minute second behavior

where subject, minute, and second must be whole numbers, and behavior must be a single character
(I, S, C, or E) for immobility, swimming, climbing, or end of test, respectively, reflecting
the time of **ONSET** for that behavior.

For each subject the first line must be set to:
	subject 0 0 behavior
And the last line must be set to:
	subject 5 0 E

The subject number must repeat on every line corresponding to that subject.
Here is an example of properly formatted data for two subjects, numbered 1 and 2:

1	0	0	I
1	0	7	S
1	0	18	I
1	1	11	S
1	1	24	I
1	5	0	E
2	0	0	S
2	0	56	I
2	1	5	S
2	3	28	I
2	3	32	S
2	3	37	I
2	5	0	E

**IMPORTANT**: You must save this data as a txt file named "FSTdata.txt" and copy this file to *THIS FOLDER*.

Then double click on "FST.exe", and the computer will generate a file in this folder called
"FSTsummary.txt." The FST summary file will be overwritten the next time the FST program is run,
so you should **IMMEDIATELY MOVE THIS FILE** to another folder, where it can be opened from Excel
and saved as an Excel file.

--Jason Shumake

*DISCLAIMER*: This only works for the 5 minute version of the test.