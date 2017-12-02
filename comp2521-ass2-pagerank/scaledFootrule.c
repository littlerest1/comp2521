#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include <math.h>
#include <assert.h>
#include "part3.h"
#define MAXLINE 1000

int alreadyIn(int columns[],int j,int size);
int main(int argc,char *argv[]){	
	//1: store the union set of the urls into a linklist 
	if(argc < 2){
		printf("please give rank.txt\n");
		exit(1);
	}
	
	List list = newList();
	assert(list != NULL);
	int k = 1;
	for(k = 1;k < argc;k++){
		FILE *fp = fopen(argv[k], "r");
		if(fp == NULL){printf("open error\n");exit(1);}
		char urls[MAXLINE];
		char *f;
		while((fscanf(fp,"%s",urls)) == 1){
			  if((f = strstr(urls, "url"))){
				ListInsert(list,f);		  
			  }
		}
		fclose(fp);
	}
	//debug func:
	//printList(list);
	
	//create a matrix for algorithm W(c,p)in T1 +W(c,p)in T2 ..
	int size = NumofV(list);
        double matrixOri[size + 1][size + 1];
	double matrix[size + 1][size + 1];
	int i,j;
	int p = 0,p1 = 0;
	double value = 0.0;
	
	for(i = 1;i < size + 1;i++){
		for(j = 1;j < size + 1;j++){
			for(k = 1;k < argc;k++){
				FILE *xp;
				char url[MAXLINE];
				if((xp = fopen(argv[k],"r")) == NULL){
				   printf("open %s error\n",argv[k]);
				   exit(1);
				}
				while((fscanf(xp,"%s",url)) == 1){
					if(strcmp(findVer(list,j-1),url)==0){
					    p1 = p + 1;
					    // p1 = url's order in file
					    // p is nums of url in file
					}
					p++;
				}
				//i is the row in matrix which equals to position are placing
				double x = (double)p1/p;
				double y = (double)i/size;
				if(p1 == 0)y = 0;
			        value += fabs(x-y);				
				p = 0;
				p1 = 0;
				fclose(xp);
			}
			matrixOri[i][j] = value;
			matrix[i][j] = value;
			
			value = 0.0;
		}
	}
	/* debug func. : printing original matrix just formed
	for(i=1;i<size+1;i++){
		for(j=1;j<size+1;j++){
			printf("%.6lf ",matrix[i][j]);
		}
		printf("\n");
	}
	*/
	// starting Hungarian algorithm
	//phrase 1: a) find out the smallest num in each row and subtract that
	int count;
	double comp = 0.0;
	
	for(i = 1;i < size + 1;i++){
		comp = matrix[i][1];
		for(j = 1;j < size + 1;j++){
			if(comp - matrix[i][j] > 0.0){
			   comp = matrix[i][j];
		    }
		}
		for(count = 1;count < size + 1;count++){
			matrix[i][count] -= comp;
		}
	}
	/*debug func. print out the matrix after first operation
        printf("\n");
	for(i=1;i<size+1;i++){
		for(j=1;j<size+1;j++){
			printf("%.6lf ",matrix[i][j]);
		}
		printf("\n");
	}
	*/
	//find out the minimum value in each column and subtract it
	for(i = 1;i < size + 1;i++){
		comp = matrix[1][i];
		for(j = 1;j < size + 1;j++){
			if(comp - matrix[j][i] > 0.0){
			   comp = matrix[j][i];
		    }
		}
	//	printf("comp%.6lf\t",comp);
		for(count = 1;count < size + 1;count++){
			matrix[count][i] -= comp;
		}
	}
	/*debug func print out the matrix
	printf("\n");
	for(i=1;i<size+1;i++){
		for(j=1;j<size+1;j++){
			printf("%.6lf ",matrix[i][j]);
		}
		printf("\n");
	}
	*/
	//step 2: row scaning if the row has only one '0' mark its position and 'delete' that column
	ZeroList zl = newZeroList();
	assert(zl);
	int columns[size];
	int rows[size];
	int c;
	for(c = 0;c < size;c++){
		columns[c] = -1;
		rows[c] = -1;
	}
	c = 0;
	for(i = 1;i < size + 1;i++){
		int zeros = 0;
		for(j = 1;j < size + 1;j++){
			if(matrix[i][j] == 0.0){
				zeros ++;
		    }
		}
		//printf("in row %d has zero %d\n",i,zeros);
		if(zeros == 1){
			for(count = 1;count < size + 1;count++){
			    if(matrix[i][count] == 0.0){
					if(alreadyIn(columns,count,size) == 1)continue;
					else{
						ZeroInsert(zl,i,count);
					//	printf("i = %d count =%d\n",i,count);
						columns[c] = count;
						c++;
					}
				}
			}
	    }
	}
	/*debug print func.
	for (i = 0 ;i<size;i++){
		printf("c:%d\t",columns[i]);
	}
   	 printZeros(zl);
	printf("\n\n");
	*/
	for(i = 1;i < size + 1;i++){
		int zeros = 0;
		for(j = 1;j < size + 1;j++){
			if(alreadyIn(columns,j,size) == 1)continue;
			if(matrix[i][j] == 0.0){
				zeros ++;
		    }
		}
		//printf("in row %d has zero %d\n",i,zeros);
		if(zeros == 1){
			for(count = 1;count < size + 1;count++){
				if(alreadyIn(columns,count,size) == 1)continue;
			    if(matrix[i][count] == 0.0){
				//	printf("[%d][%d]\n",i,count);
					ZeroInsert(zl,i,count);
					columns[c] = count;
					c++;
				}
			}
	    }
	}
	/*debug func
		printf("\ncolumns:\t");	
		for(i=0;i<size;i++){
			printf("%d\t",columns[i]);
		}
	*/
///////////////////////////////////////////////	column scaning find out the column has only one '0',mark it and 'delete' the row 
    	int r = 0;
	for(i = 1;i < size + 1;i++){
		int zeros = 0;
		for(j = 1;j < size + 1;j++){
			if(alreadyIn(columns,i,size) == 1)continue;
			if(matrix[j][i] == 0.0){
				zeros ++;
		    }
		}
		if(zeros == 1){
			for(count = 1;count < size + 1;count++){
				if(alreadyIn(rows,count,size) == 1)continue;
			    if(matrix[count][i] == 0.0){
					ZeroInsert(zl,count,i);
					rows[r] = count;
					r++;
				}
			}
	    }
	}
		 printZeros(zl);
	//if no row's has only one '0' it mean's operation completed and has 2 or more possible sol. just get the first sol and print out
	int x = NumofZeros(zl);
	if(x == size){
	   for(i = 1;i < size + 1;i++){
		   for(j = 1;j < size + 1;j++){
			   if(alreadyIn(columns,j,size) == 1)continue;
			   if(matrix[i][j] == 0.0){
				   columns[c] = j;
				   ZeroInsert(zl,i,j);
				   c++;
				   break;
			   }
		   }
	   }
	   /*debug func print row and column that has been deleted
	   printZeros(zl);
		printf("\nrow:\t");
		for(c=0;c<size;c++){
			printf("%d\t",rows[c]);
		}
		printf("\ncolumns:\t");	
		for(c=0;c<size;c++){
			printf("%d\t",columns[c]);
		}
	 */
		//final print out the urls in correct position which has minimum distance
		double dist = 0.0;
		for(i = 1;i < size + 1;i++){
			int final = finalColumns(zl,i);
			if(final == 0)continue;
			dist += matrixOri[i][final];
		}
		printf("%.6lf\n",dist);
		
		printZeroList(zl,list,size);
	}
	else{
	   
		//it need to have more operation
		/*debug func print out the situation of 'now'
		printf("size=%d\n",size);
		printZeros(zl);
		printf("row:\t");
		for(c=0;c<size;c++){
			printf("%d\t",rows[c]);
		}
		printf("\ncolumns:\t");	
		for(c=0;c<size;c++){
			printf("%d\t",columns[c]);
		}
		*/
		int i = NumofZeros(zl);
		// if num of zeros = size means complete its operation
		if(i == size){
		   double dist = 0.0;
			for(i = 1;i < size + 1;i++){
				int final = finalColumns(zl,i);
				if(final == 0)continue;
				dist += matrixOri[i][final];
			}
			printf("%.6lf\n",dist);
			
			printZeroList(zl,list,size);
		}
		else{
			//step 3: find out the minimum value in the undeleted rows or columns
			comp = 1.0;
			for(i = 1;i < size + 1;i++){
				for(j = 1;j < size + 1;j++){
					if(alreadyIn(columns,j,size) == 1 || alreadyIn(rows,i,size) == 1)continue;
					else if(comp - matrix[i][j] > 0.0)comp = matrix[i][j];
				}
			}
			
			//printf("comp = %.5lf\n",comp);
			//subtract the minimum value of the values in the undeleted area also add the minimum value in the intersection point
			//also create a new matrix to store the new matrix
			double matrixtemp[size+1][size+1];
			for(i = 1;i < size + 1;i++){
				for(j = 1;j < size + 1;j++){
					if(alreadyIn(columns,j,size) == 1 && alreadyIn(rows,i,size) == 1){
					   matrixtemp[i][j] = matrix[i][j] + comp;
					}
					else if(alreadyIn(columns,j,size) == 1 || alreadyIn(rows,i,size) == 1)
					{
						matrixtemp[i][j] = matrix[i][j];
					}
					else{
						 matrixtemp[i][j] =   matrix[i][j] - comp;
					}
				}
			}
			/*debug print func.
			for(i=1;i<size+1;i++){
				for(j=1;j<size+1;j++){
					printf("%.6lf ",matrixtemp[i][j]);
				}
				printf("\n");
			}
			printf("new:\n");
			*/
			//repeat step 1
			ZeroList zlsec = newZeroList();
			assert(zlsec);
			int columnsec[size];
			int rowsec[size];
			int c;
			for(c = 0;c < size;c++){
				columnsec[c] = -1;
				rowsec[c] = -1;
			}
			c = 0;
			for(i = 1;i < size + 1;i++){
				int zeros = 0;
				for(j = 1;j < size + 1;j++){
					if(matrixtemp[i][j] == 0.0){
						zeros ++;
					}
				}
				//printf("in row %d has zero %d\n",i,zeros);
				if(zeros == 1){
					for(count = 1;count < size + 1;count++){
						if(matrixtemp[i][count] == 0.0){
							if(alreadyIn(columnsec,count,size) == 1)continue;
							else{
								ZeroInsert(zlsec,i,count);
								//printf("i = %d count =%d\n",i,count);
								columnsec[c] = count;
								c++;
							}
						}
					}
				}
			}
			/*debug print func
			for (i = 0 ;i<size;i++){
				printf("c:%d\t",columnsec[i]);
			}
			printZeros(zlsec);
			*/
			for(i = 1;i < size + 1;i++){
				int zeros = 0;
				for(j = 1;j < size + 1;j++){
					if(alreadyIn(columnsec,j,size) == 1)continue;
					if(matrixtemp[i][j] == 0.0){
						zeros ++;
					}
				}
				//printf("in row %d has zero %d\n",i,zeros);
				if(zeros == 1){
					for(count = 1;count < size + 1;count++){
						if(alreadyIn(columnsec,count,size) == 1)continue;
						if(matrixtemp[i][count] == 0.0){
						//	printf("[%d][%d]\n",i,count);
							ZeroInsert(zlsec,i,count);
							columnsec[c] = count;
							c++;
						}
					}
				}
			}
			
			printf("\ncolumns:\t");	
			for(i=0;i<size;i++){
				printf("%d\t",columnsec[i]);
			}
			int r = 0;
			for(i = 1;i < size + 1;i++){
				int zeros = 0;
				for(j = 1;j < size + 1;j++){
					if(alreadyIn(columnsec,i,size) == 1)continue;
					if(matrixtemp[j][i] == 0.0){
						zeros ++;
					}
				}
				if(zeros == 1){
					for(count = 1;count < size + 1;count++){
						if(alreadyIn(rowsec,count,size) == 1)continue;
						if(matrixtemp[count][i] == 0.0){
							ZeroInsert(zlsec,count,i);
							rowsec[r] = count;
							r++;
						}
					}
				}
			}
			printf("\nrows:\t");	
			for(i=0;i<size;i++){
				printf("%d\t",rowsec[i]);
			}
			if(rowsec[0] == -1){
				for(i = 1;i < size + 1;i++){
					   for(j = 1;j < size + 1;j++){
						   if(alreadyIn(columnsec,j,size) == 1)continue;
						   if(matrixtemp[i][j] == 0.0){
							   columnsec[c] = j;
							   ZeroInsert(zlsec,i,j);
							   c++;
							   break;
						   }
					   }
				}
				/*debug print
				printZeros(zlsec);
				printf("\nrow:\t");
				for(c=0;c<size;c++){
					printf("%d\t",rowsec[c]);
				}
				printf("\ncolumns:\t");	
				for(c=0;c<size;c++){
					printf("%d\t",columnsec[c]);
				}
				*/
				double dist = 0.0;
				for(i = 1;i < size + 1;i++){
					int final = finalColumns(zlsec,i);
					if(final == 0)continue;
					dist += matrixOri[i][final];
				}
				//printZeros(zlsec);
				printf("%.6lf\n",dist);

				printZeroList(zlsec,list,size);		
			
		    }
		    else{
		         printf("\n");
		         for(i = 1;i<size+1;i++){
		             for(j=1;j<size+1;j++){
		                printf("%.2lf ",matrixtemp[i][j]);
		             }
		             printf("\n");
		         }
		         for(i = 1;i<size+1;i++){
		             for(j=1;j<size+1;j++){
		                if(alreadyIn(columnsec,j,size) == 1 || alreadyIn(rowsec,i,size))continue;
		                if(matrixtemp[i][j] == 0.0){
		                  ZeroInsert(zlsec,i,j);
		                  columnsec[c] = j;
		                  c++;
		                  rowsec[r] = i;
		                  r++;
		                }
		             }
		         }
		        printZeros(zlsec);
				printf("\nrow:\t");
				for(i=0;i<size;i++){
					printf("%d\t",rowsec[i]);
				}
				printf("\ncolumns:\t");	
				for(i=0;i<size;i++){
					printf("%d\t",columnsec[i]);
				}
				int nz = NumofZeros(zlsec);
		        if(nz == size){
		           double dist = 0.0;
			        for(i = 1;i < size + 1;i++){
				        int final = finalColumns(zlsec,i);
				        if(final == 0)continue;
				        dist += matrixOri[i][final];
			        }
			        printf("%.6lf\n",dist);
			
			        printZeroList(zl,list,size);
		        }
		        else{
                     int lost[size] = {-1};
                     int  lo = 0;
                     for(i = 1;i < size + 1;i++){
                         if(alreadyIn(columnsec,i,size) == 0){
                            lost[lo] = i;
                            lo ++;
                         }
                     }
                     lo = 0;
                     for(i=0;i<size;i++){
                     printf("lost = %d\n",lost);
                     }
                     int col = 0;
                     for(i = 1;i < size;i++){
                         for(lo = 0;lo < size;lo++){
                             if(lost[lo]!=-1)int Lost = lost[lo]
                             double com = matrixtemp[Lost][0];
                             if(alreadyIn(columnsec,i,size)== 1)continue;
                             if(matrixtemp[Lost][i] -  com > 0.0){
                                com = matrixtemp[Lost][i];
                                col = i;
                             }
                         }
                     }
                     ZeroInsert(zlsec,lost,col);
                     printZeros(zlsec);
                     int nz = NumofZeros(zlsec);
		             if(nz == size){
		             double dist = 0.0;
			         for(i = 1;i < size + 1;i++){
				            int final = finalColumns(zlsec,i);
				            if(final == 0)continue;
				            dist += matrixOri[i][final];
			         }
			         printf("%.6lf\n",dist);
			
			         printZeroList(zlsec,list,size);
		        }
                     
                     
		        }
		         
		    }
		   
	    }
	}
	return 0;
}

int alreadyIn(int columns[],int j,int size){
	int c = 0;
	for(;c < size;c++){
		if(columns[c] == j)return 1;
	}
	return 0;
}
