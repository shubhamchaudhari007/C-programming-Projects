#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "decode.h"
#include <string.h>

OperationType check_operation_type(char *);

int main(int argc, char *argv[])
{
    /*
     * Simple CLI entry point for the steganography tool.
     * Usage examples:
     *  - Encoding: a.out -e <source.bmp> <secret.txt> [output.bmp]
     *  - Decoding: a.out -d <stego.bmp> [output_secret_base]
     */

    // Step 1 : Check the argc >= 4 true - > step 2
    if (argc >= 4)
    {
        // Step 2 : Call the check_operation_type(argv[1]) == e_encode )) true - > step 3
        if (check_operation_type(argv[1]) == e_encode)
        {
            // Step 3 : Declare structure variable EncodeInfo enc_info
            EncodeInfo enc_Info;
            // Step 4 : Call the read_and_validate_encode_args(argv,&enc_info)== e_success)
            if (read_and_validate_encode_args(argv, &enc_Info) == e_success)
            {
                //  true -> Step 5 ,
                // Step 5 : Call the do_encoding (&encInfo);
                if (do_encoding(&enc_Info) == e_success)
                {
                    printf("Encoding completed successfully. Output stego file: %s\n", enc_Info.stego_image_fname);
                }
            }
            else
            {
                // false - > terminate the program

                return 0;
            }
        }
        else if (check_operation_type(argv[1]) == e_decode)
        {
            // for decoding
            DecodeInfo dcd_Info;

            if (read_and_validate_decode_args(argv, &dcd_Info) == e_success)
            {
                // open .bmp file to read magic string and check the file is encoded or not
                open_file_decode(&dcd_Info);

                // check magic string is present or not
                if (decode_magic_string(&dcd_Info) == e_success)
                {
                    printf("Input file appears to contain embedded data. Starting decode...\n");
                    // do decoding
                    if (do_decoding(&dcd_Info) == e_success)
                    {
                        printf("Decoding completed successfully. Output: %s\n", dcd_Info.secret_fname);
                    }
                    else
                    {
                        printf("Error: decoding failed.\n");
                    }
                }
                else
                {
                    printf("The provided file does not appear to be encoded. Please supply a valid encoded BMP.\n");
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            printf("Unsupported operation. Use -e to encode or -d to decode.\n");
            return 0;
        }
    }
    else
    {
        printf("Insufficient arguments. See usage: a.out -e <source.bmp> <secret> [output.bmp]  OR  a.out -d <stego.bmp> [output_secret_base]\n");
        return 0;
    }
}

OperationType check_operation_type(char *symbol)
{

    if (!strcmp(symbol, "-e"))
    {
        // Step 1 : Check whether the symbol is -e or not true - > return e_encode false -> Step 2
        return e_encode;
    }
    else if (!strcmp(symbol, "-d"))
    {
        // Step 2 : Check whether the symbol is -d or not true - > return e_decode
        return e_decode;
    }
    else
    {
        // false -> return e_unsupported
        return e_unsupported;
    }
}
