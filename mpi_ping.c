#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void)
{
   int   comm_sz;
   int   my_rank;
   int   valor=0;
   int   count = 5;

   /* Iniciar MPI */
   MPI_Init(NULL, NULL); 

   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   if (my_rank != 0)
   {
      for (int i=0; i<count; i++)
      {
         /* Recibir mensaje del proceso 0 */
         printf("1 Recibe un incremento de 0, valor: %d \n", valor);
         MPI_Recv(&valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         valor+=1;
         /* Enviar mensaje al proceso 0 */
         printf("1 Envia un incremento a 0\n");
         MPI_Send(&valor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      }
   }

   else
   {
      for (int i=0; i<count; i++)
      {
         valor+=1;
         /* Enviar mensaje al proceso 1 */
         printf("0 Envia un incremento a 1\n");
         MPI_Send(&valor, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

         /* Recibir mensaje del proceso 1 */
         printf("0 Recibe un incremento de 1, valor: %d \n", valor);
         MPI_Recv(&valor, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      printf("total: %d\n", valor);
   }

   /* Apagar MPI */
   MPI_Finalize(); 

   return 0;
}