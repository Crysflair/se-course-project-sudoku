# Personal Project of SE course: sudoku
This is a repository for the course project of software engineering(BIT, 2018).  
It includes a program to automatically generate Sudoku problems. Possibly a GUI would be added. (Maybe never now)
link to blog: https://blog.csdn.net/qq_36965871/article/details/84898541

## Quick Start
1. Download /BIN. 
2. Lauch "soduku.exe" in command line.
Parameter setting:
- -c $integer:  
create $integer sudoku filled map and export to ./soduku.txt
- -s $path:   
read soduku puzzles from $path, and export the solution to ./soduku.txt

## Format
Maps are seperated with a blank line.   
The last map(9×9) has no new line at the end.  
**example**:

```
9	0	8	0	6	0	1	2	4 
2	3	7	4	5	1	9	6	8 
1	4	6	0	2	0	3	5	7 
0	1	2	0	7	0	5	9	3 
0	7	3	0	1	0	4	8	2 
4	8	0	0	0	5	6	0	1 
7	0	4	5	9	0	8	1	6 
8	9	0	7	4	6	2	0	0 
3	0	5	0	8	0	7	0	9 
9	0	0	8	0	0	4	0	0 

9	0	8	0	6	0	1	2	4 
2	3	7	4	5	1	9	6	8 
1	4	6	0	2	0	3	5	7 
0	1	2	0	7	0	5	9	3 
0	7	3	0	1	0	4	8	2 
4	8	0	0	0	5	6	0	1 
7	0	4	5	9	0	8	1	6 
8	9	0	7	4	6	2	0	0 
3	0	5	0	8	0	7	0	9 
9	0	0	8	0	0	4	0	0 
```

