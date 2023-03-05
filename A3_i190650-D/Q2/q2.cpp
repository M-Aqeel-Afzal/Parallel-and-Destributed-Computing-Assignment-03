#include <unistd.h>
#include <omp.h>
#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maximum 100000            
using namespace std;

int main(int argc, char** argv)
{


    int rank,size = 100,dis_t,p_size,processes,recvmaster
,size_of_recv,count = 0,req_num,founded = 1,abort = 0,not_founded = 0;                                      
    int* data;                                       
    int* send;
    int* recvslave;                
              

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    processes = p_size;
  
    if (rank == 0)                                                          
    {  
        MPI_Status status;
        cout<<"Enter required number to search(between 0 to 100) = ";
        cin>> req_num;
        cout<<"\n\n";
        data = new int[size];                                               
       
        int x = 1;
        for (int i=0; i<size; i++)                                          
        {
            data[i] = x;
            x++;
        }

        if ((size % (processes-1)) == 0)                                   
        {
            dis_t = size / (processes-1);
            send = new int[size];  
        }

        for (int i =1; i< processes; i++)                                  
        {
            for (int j=count; j<(count+dis_t); j++)
            {
                send[j] = data[j];
            }

            #pragma omp critical                                                             
   {
                MPI_Send(send+count,dis_t, MPI_INT, i, 6, MPI_COMM_WORLD);                     
                count+=dis_t;
                MPI_Send(&req_num,1, MPI_INT, i, 6, MPI_COMM_WORLD);                       

            }            
        }

        MPI_Recv (&recvmaster, 1, MPI_INT,MPI_ANY_SOURCE,6, MPI_COMM_WORLD, &status);         

        if (recvmaster == founded)                                                           
        {
            cout<<"master:   SLAVE "<<status.MPI_SOURCE<<" found the value\n\n";
           
            for (int i=1; i<processes; i++)
            {
                cout<<"master: sending absort message to salve: "<<i<<endl;
                MPI_Send(&abort,1, MPI_INT, i, 6, MPI_COMM_WORLD);                        
            }
           
        }
                                                                               
    }

    else
    {
        int req_num1,abort_num1;
        bool founded1 = false;
                                                                               
        #pragma omp parallel num_threads(1)                                                    
        {
            recvslave = new int[size];                                                        
            MPI_Status status;                                                               
            #pragma omp critical
            {
                
                MPI_Recv (recvslave, maximum, MPI_INT,0,6, MPI_COMM_WORLD, &status);          
                MPI_Get_count(&status, MPI_INT,&size_of_recv);                                
                cout<<"slave "<<rank<<": ";  
               
                    for (int i =0; i<size_of_recv; i++)
                    {
                        cout<<recvslave[i]<<" ";                                               
                    }
                    cout<<"\n\n\n\n";

                #pragma omp_barrier                                                           
                {
                    int idx;  
                    MPI_Recv (&req_num1, 1, MPI_INT,0,6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);    
                   
                   
                    for (int i = 0; i < size_of_recv; i++)                                      
                    {
                        if (recvslave[i] == req_num1)                                         
                        {
                            idx =  i;
                            founded1 = true;
                        }
                    }

                    if (founded1 == true)
                    {
                        cout<<"slave "<<rank <<": i have founded the value at index: "<<idx<<endl<<endl;
                        cout<<"slave "<<rank<<": sending message to master that value has been found..."<<endl;
                        MPI_Send(&founded,1, MPI_INT, 0, 6, MPI_COMM_WORLD);                    
                    }
                    else
                    {
                       
                        cout<<"Slave "<<rank<<": i did't found the value!"<<endl;                      
                    }
                }  
            }
            
            MPI_Recv (&abort_num1, 1, MPI_INT,0,6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);             
           
            if (abort_num1 == abort)
            {
                cout<< "Slave "<<rank<<": absort signal founded!"<<endl;
            }
        }      
    }
    MPI_Finalize();
    return 0;
}

