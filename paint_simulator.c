#include <stdio.h>
#include <stdlib.h>

#define EPERM 1
#define EINVAL 2
#define ENOMEM 3


		// definirea structurii
typedef struct {
   		unsigned char r, g, b;
	} pixel;


pixel** init_image(pixel **image, short old_height, short height, short width){

	short i, j;

	if(old_height > height){
		for(i = height; i < old_height; i++) free(image[i]);
	}
	image = realloc(image, height * sizeof(pixel* ));
	if(image == NULL){
			fflush(stdout);
			fprintf(stderr, "%d\n", ENOMEM);
 			exit(EXIT_FAILURE);
			}
	if(old_height < height){
		for(i = old_height; i < height; ++i) image[i] = malloc(sizeof(pixel));
	}
	
	for (i = 0; i < height; i++)
		{
		image[i] = realloc( image[i], width * sizeof(pixel));

		if(image[i] == NULL){
			fflush(stdout);
			fprintf(stderr, "%d\n", ENOMEM);
 			exit(EXIT_FAILURE);
			}	
		}


	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++){
			scanf("%hhu", &image[i][j].r);
				if( image[i][j].r > 255 || image[i][j].r < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}
				
				scanf("%hhu", &image[i][j].g);
				if( image[i][j].g > 255 || image[i][j].g < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hhu", &image[i][j].b);
				if( image[i][j].b > 255 || image[i][j].b < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}
		}

	return image;
}

void print(pixel **image, short height, short width){

	short i, j;
	
	printf("%hd %hd\n", width, height);

	for (i = 0; i < height; i++){
			for (j = 0; j < width; j++){
				printf("%hhu ", image[i][j].r);
				printf("%hhu ", image[i][j].g);
				printf("%hhu ", image[i][j].b);
			}
			printf("\n");
		}
		
}

pixel **crop(pixel **image, short height, short width, short start_col, short start_line, short end_col, short end_line){

	short i, j;
	pixel** image2;

	image2 = malloc( (end_line - start_line +1) * sizeof(pixel*));

	if(image2 == NULL){
		fflush(stdout);
		fprintf(stderr, "%d\n", ENOMEM);
 		exit(EXIT_FAILURE);
		}

	for( i = 0 ; i < end_line - start_line +1 ; i++ ){

		image2[i] = malloc( (end_col - start_col + +1) * sizeof(pixel));

		if(image2[i] == NULL){
			fflush(stdout);
			fprintf(stderr, "%d\n", ENOMEM);
 			exit(EXIT_FAILURE);
			}
	}

	

	for (i = 0; i < end_line - start_line + +1; i++)
		for (j = 0; j < end_col - start_col + +1; j++){
			image2[i][j].r = image[i + start_line][j + start_col].r;
			image2[i][j].g = image[i + start_line][j + start_col].g;
			image2[i][j].b = image[i + start_line][j + start_col].b;
		}
	
	for (i = 0; i < height; i++)
		free(image[i]);

	free(image);

	return image2;

}


pixel** color_reg(pixel **image, short start_col, short start_line, short end_col, short end_line, pixel color){

	short i, j;

	for (i = start_line; i <= end_line; i++)
		for (j = start_col; j <= end_col; j++){
			image[i][j].r = color.r;
			image[i][j].g = color.g;
			image[i][j].b = color.b;
		}
	return image;
}

pixel** Blur(pixel **image, short height, short width){

	short i, j;
	
	pixel** image2;

	image2 = malloc( height * sizeof(pixel* ));

	if(image2 == NULL){
		fflush(stdout);
		fprintf(stderr, "%d\n", ENOMEM);
 		exit(EXIT_FAILURE);
		}
	
	for (i = 0; i < height; i++){
		image2[i] = malloc(width * sizeof(pixel));
		if(image2[i] == NULL){
			fflush(stdout);
			fprintf(stderr, "%d\n", ENOMEM);
 			exit(EXIT_FAILURE);
			}
		}

	

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++){
			image2[i][j].r = image[i][j].r;
			image2[i][j].g = image[i][j].g;
			image2[i][j].b = image[i][j].b;
		}


			// colt stanga sus
	image[0][0].r = ( image2[0][1].r + image2[1][0].r ) / 2;
	image[0][0].g = ( image2[0][1].g + image2[1][0].g ) / 2;
	image[0][0].b = ( image2[0][1].b + image2[1][0].b ) / 2;


			// colt dreapta sus
	image[0][width-1].r = ( image2[0][width-2].r + image2[1][width-1].r ) / 2;
	image[0][width-1].g = ( image2[0][width-2].g + image2[1][width-1].g ) / 2;
	image[0][width-1].b = ( image2[0][width-2].b + image2[1][width-1].b ) / 2;
	

			// colt stanga jos
	image[height-1][0].r = ( image2[height-2][0].r + image2[height-1][1].r ) / 2;
	image[height-1][0].g = ( image2[height-2][0].g + image2[height-1][1].g ) / 2;
	image[height-1][0].b = ( image2[height-2][0].b + image2[height-1][1].b ) / 2;


			//colt dreapta jos
	image[height-1][width-1].r = ( image2[height-2][width-1].r + image2[height-1][width-2].r ) / 2;
	image[height-1][width-1].g = ( image2[height-2][width-1].g + image2[height-1][width-2].g ) / 2;
	image[height-1][width-1].b = ( image2[height-2][width-1].b + image2[height-1][width-2].b ) / 2;


			// latura stanga
	for (i = 1 ; i < height - 1; i++){
		image[i][0].r = ( image2[i-1][0].r + image2[i+1][0].r + image2[i][1].r ) / 3;
		image[i][0].g = ( image2[i-1][0].g + image2[i+1][0].g + image2[i][1].g ) / 3;
		image[i][0].b = ( image2[i-1][0].b + image2[i+1][0].b + image2[i][1].b ) / 3;
	}

			// latura sus
	for (j = 1 ; j < width - 1; j++){
		image[0][j].r = ( image2[0][j-1].r + image2[0][j+1].r + image2[1][j].r ) / 3;
		image[0][j].g = ( image2[0][j-1].g + image2[0][j+1].g + image2[1][j].g ) / 3;
		image[0][j].b = ( image2[0][j-1].b + image2[0][j+1].b + image2[1][j].b ) / 3;
	}

			// latura jos
	for (j = 1 ; j < width - 1; j++){
		image[height-1][j].r = ( image2[height-1][j-1].r + image2[height-1][j+1].r + image2[height-2][j].r ) / 3;
		image[height-1][j].g = ( image2[height-1][j-1].g + image2[height-1][j+1].g + image2[height-2][j].g ) / 3;
		image[height-1][j].b = ( image2[height-1][j-1].b + image2[height-1][j+1].b + image2[height-2][j].b ) / 3;
	}
	
			// latura dreapta
	for (i = 1 ; i < height - 1; i++){
		image[i][width-1].r = ( image2[i-1][width-1].r + image2[i+1][width-1].r + image2[i][width-2].r ) / 3;
		image[i][width-1].g = ( image2[i-1][width-1].g + image2[i+1][width-1].g + image2[i][width-2].g ) / 3;
		image[i][width-1].b = ( image2[i-1][width-1].b + image2[i+1][width-1].b + image2[i][width-2].b ) / 3;
	}


			// interior
	for (i = 1; i < height - 1; i++)
		for (j = 1; j < width - 1; j++){
			image[i][j].r = ( image2[i][j-1].r + image2[i][j+1].r + image2[i-1][j].r + image2[i+1][j].r ) / 4;
			image[i][j].g = ( image2[i][j-1].g + image2[i][j+1].g + image2[i-1][j].g + image2[i+1][j].g ) / 4;
			image[i][j].b = ( image2[i][j-1].b + image2[i][j+1].b + image2[i-1][j].b + image2[i+1][j].b ) / 4;
	}

	for (i = 0; i < height; i++)
		free(image2[i]);

	free(image2);

	return image;
}


pixel** Rotate(pixel **image, short height, short width){

	short i, j;
	pixel** image2;


	image2 = malloc( height * sizeof(pixel* ));

	if(image2 == NULL){
		fflush(stdout);
		fprintf(stderr, "%d\n", ENOMEM);
 		exit(EXIT_FAILURE);
		}
	
	for (i = 0; i < height; i++){
		image2[i] = malloc(width * sizeof(pixel));
		if(image2[i] == NULL){
			fflush(stdout);
			fprintf(stderr, "%d\n", ENOMEM);
 			exit(EXIT_FAILURE);
			}
		}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++){
			image2[i][j].r = image[i][j].r;
			image2[i][j].g = image[i][j].g;
			image2[i][j].b = image[i][j].b;
		}

	for (i = 0; i < height; i++)
		free(image[i]);

	free(image);

	image = malloc( width * sizeof(pixel* ));
	for (i = 0; i < width; i++)
		image[i] = malloc( height * sizeof(pixel));

	if(image == NULL){
		fflush(stdout);
		fprintf(stderr, "%d\n", ENOMEM);
 		exit(EXIT_FAILURE);
		}

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++){
			image[j][i].r = image2[height-i-1][j].r;
			image[j][i].g = image2[height-i-1][j].g;
			image[j][i].b = image2[height-i-1][j].b;
		}

	for (i = 0; i < height; i++)
		free(image2[i]);

	free(image2);

	return image;
}


void Fill(pixel **image, short line, short col, short height, short width, pixel aux, pixel color)
{	

	image[line][col].r = color.r;
	image[line][col].g = color.g;
	image[line][col].b = color.b;	

	if(line < height-1)
		if((image[line+1][col].r == aux.r) && (image[line+1][col].g == aux.g) && (image[line+1][col].b == aux.b))
			Fill(image, line+1, col, height, width, aux, color);
	
	if(line > 0)
		if(image[line-1][col].r == aux.r && image[line-1][col].g == aux.g && image[line-1][col].b == aux.b)
			Fill(image, line-1, col, height, width, aux, color);

	
	if(col < width-1)
		if(image[line][col+1].r == aux.r && image[line][col+1].g == aux.g && image[line][col+1].b == aux.b)
			Fill(image, line, col+1, height, width, aux, color);	

	if(col > 0)
		if(image[line][col-1].r == aux.r && image[line][col-1].g == aux.g && image[line][col-1].b == aux.b)
			Fill(image, line, col-1, height, width, aux, color);	
		
}



int main(void){
				// declarari variabile
	short height, width, height_3, width_3, i, j, num_iter;
	short start_col, start_line, end_col, end_line, aux;	
	char opCode, num_rot;
	pixel color, aux_color;
	
	pixel **image;

	scanf("%hhu", &opCode);

	if( opCode == 1 ){
		
		scanf("%hd", &width);			
		if( width > 1024 || width < 1){
			fflush(stdout);
			fprintf(stderr, "%d\n", EINVAL);
 			exit(EXIT_FAILURE);
		}

		scanf("%hd", &height);
		if( height > 1024 || height < 1){
			fflush(stdout);
			fprintf(stderr, "%d\n", EINVAL);
 			exit(EXIT_FAILURE);
		}

		image = malloc( height * sizeof(pixel* ));

		if(image == NULL){
			fflush(stdout);
			fprintf(stderr, "%d\n", ENOMEM);
 			exit(EXIT_FAILURE);
		}

		for (i = 0; i < height; i++){
			image[i] = malloc(width * sizeof(pixel));
			if(image[i] == NULL){
				fflush(stdout);
				fprintf(stderr, "%d\n", ENOMEM);
 				exit(EXIT_FAILURE);
			}
		}
		


		for (i = 0; i < height; i++)
			for (j = 0; j < width; j++){
				scanf("%hhu", &image[i][j].r);
				if( image[i][j].r > 255 || image[i][j].r < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}
				
				scanf("%hhu", &image[i][j].g);
				if( image[i][j].g > 255 || image[i][j].g < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hhu", &image[i][j].b);
				if( image[i][j].b > 255 || image[i][j].b < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}
			}
	
	}
	else{
	fflush(stdout);
	fprintf(stderr, "%d\n", EPERM);
 	exit(EXIT_FAILURE);
	}


	scanf("%hhu", &opCode);

	while(opCode != 0){		
		
		switch(opCode){

			case 1:
				scanf("%hd", &width);			
				if( width > 1024 || width < 1){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hd", &aux);
				if( height > 1024 || height < 1){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}
				
				image = init_image(image, height, aux, width);
				height = aux;
				break;
		
			case 2:
				scanf("%hd%hd", &start_col, &start_line);
				scanf("%hd%hd", &end_col, &end_line);

				if(start_col < 0 || start_col > end_col || end_col >= width){

					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}


				if(start_line < 0 || start_line > end_line || end_line >= height){

					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				image = crop(image, height, width, start_col, start_line, end_col, end_line);
				
				height = end_line - start_line + 1; 
				width = end_col - start_col + 1;
				
				
				break;

			case 3:
				scanf("%hd", &width_3);			
				if( width_3 > 1024 || width_3 < 1){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hd", &height_3);
				if( height_3 > 1024 || height_3 < 1){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				// daca noua inaltime a imaginii este mai mica
				if( height_3 < height){		
					image = crop(image, height, width, 0, 0, width - 1, height_3 - 1);
					height = height_3;
					}

				// daca noua latime a imaginii este mai mica
				if( width_3 < width){
					image = crop(image, height, width, 0, 0, width_3 - 1, height - 1);
					width = width_3;
					}
					
				
				// daca noua inaltime a imaginii este mai mare
				if(height < height_3){

					image = realloc( image, height_3 * sizeof(pixel* ));

					if(image == NULL){
						fflush(stdout);
						fprintf(stderr, "%d\n", ENOMEM);
 						exit(EXIT_FAILURE);
					}
						for(i = height ; i < height_3 ; i++){
							image[i] = malloc(width * sizeof(pixel));

							if(image[i] == NULL){
								fflush(stdout);
								fprintf(stderr, "%d\n", ENOMEM);
 								exit(EXIT_FAILURE);
							}
						}

					
					
					for(i = height; i < height_3; i++)
						for(j = 0; j < width; j++){
							image[i][j].r = 255;
							image[i][j].g = 255;
							image[i][j].b = 255;
						}

					height = height_3;
				}

				// daca noua latime a imaginii este mai mare
				if(width < width_3){
					for(i = 0 ; i < height ; i++){
							image[i] = realloc(image[i],  width_3 * sizeof(pixel));	
							
							if(image[i] == NULL){
								fflush(stdout);
								fprintf(stderr, "%d\n", ENOMEM);
 								exit(EXIT_FAILURE);
							}
					}

					for(i = 0; i < height; i++)
						for(j = width; j < width_3; j++){
							image[i][j].r = 255;
							image[i][j].g = 255;
							image[i][j].b = 255;
						}
			
					width = width_3;


				}
				
				
				break;

			case 4:
				scanf("%hd%hd", &start_col, &start_line);
				scanf("%hd%hd", &end_col, &end_line);

				if(start_col < 0 || start_col > end_col || end_col >= width){

					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}


				if(start_line < 0 || start_line > end_line || end_line >= height){

					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hhu", &color.r);
				if( color.r > 255 || color.r < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hhu", &color.g);
				if( color.r > 255 || color.r < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hhu", &color.b);
				if( color.r > 255 || color.r < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}
		
				image = color_reg(image, start_col, start_line, end_col, end_line, color);

				break;

			case 5:
				scanf("%hd", &num_iter);

				if( num_iter > 2000 || num_iter < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				while(num_iter){
					image = Blur(image, height, width);
					num_iter--;
					}
				
				break;

			case 6:
				scanf("%hhu", &num_rot);

				if( num_rot > 3 || num_rot < 1){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				while(num_rot){

					image = Rotate(image, height, width);
					num_rot--;
					aux = height;
					height = width;
					width = aux;
					
					}			

				
				break;

			case 7:
				scanf("%hd%hd", &start_col, &start_line);

				if(start_col < 0 || start_col >= width){

					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				if(start_line < 0 || start_line >= height){

					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}


				scanf("%hhu", &color.r);
				if( color.r > 255 || color.r < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hhu", &color.g);
				if( color.r > 255 || color.r < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}

				scanf("%hhu", &color.b);
				if( color.r > 255 || color.r < 0){
					fflush(stdout);
					fprintf(stderr, "%d\n", EINVAL);
 					exit(EXIT_FAILURE);
				}


				aux_color.r = image[start_line][start_col].r;
				aux_color.g = image[start_line][start_col].g;
				aux_color.b = image[start_line][start_col].b;
	
				Fill(image, start_line, start_col, height, width, aux_color, color);	
				
				break;

			case 8:

				print(image, height, width);
				fflush(stdout);
				
				break;
			
			default:

				fflush(stdout);		
				fprintf(stderr, "%d\n", EPERM);
 				exit(EXIT_FAILURE);

				break;			

		}


		scanf("%hhu", &opCode);		

	}

	for (i = 0; i < height; i++)
		free(image[i]);

	free(image);

	
	return 0;
}

