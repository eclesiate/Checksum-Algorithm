#include <iostream>
#include <climits>
#ifndef MARMOSET_TESTING
int main();
#endif

unsigned int add_checksum(unsigned int n);
void add_checksum(unsigned int array[], std::size_t capacity);
bool verify_checksum(unsigned int n);
unsigned int remove_checksum(unsigned int n);
void remove_checksum(unsigned int array[], std::size_t capacity);

#ifndef MARMOSET_TESTING
int main()
{
    unsigned int value_to_protect{12345678};
    unsigned int protected_value = add_checksum(value_to_protect);
    std::cout << "The value " << value_to_protect
              << " with the checksum added is " << protected_value
              << "." << std::endl;
    if (verify_checksum(protected_value) == true)
    {
        std::cout << "The checksum is valid." << std::endl;
    }
    else
    {
        std::cout << "The checksum is invalid." << std::endl;
    }
    unsigned int v{12345678};
    unsigned int b{120};
    unsigned int a{2000000};
    unsigned int h{0};
    std::cout << "checksum of " << b << " is " << add_checksum(b) << std::endl;
    std::cout << "checksum of " << a << " is " << add_checksum(a) << std::endl;
    std::cout << "checksum of " << h << " is " << add_checksum(h) << std::endl;
    std::cout << "checksum of " << 100000000 << " is " << add_checksum(99999999+1) << std::endl;

    if (verify_checksum(b) == true) std::cout << " b valid." << std::endl;
    if (verify_checksum(add_checksum(a)) == true) std::cout << " a valid." << std::endl;
    if (verify_checksum(add_checksum(h)) == true) std::cout << " h valid." << std::endl;
    if (verify_checksum(100000000) == true) std::cout << " b valid." << std::endl;

    std::cout << remove_checksum(v) << std::endl;
    std::cout << remove_checksum(add_checksum(b)) << std::endl;
    std::cout << remove_checksum(add_checksum(a)) << std::endl;
    std::cout << remove_checksum(h) << std::endl;
    std::cout << remove_checksum(100000000) << std::endl;
    std::cout << remove_checksum(1000000000) << std::endl;

    std::cout << "checksum of 20201122 ISs " << add_checksum(20201122) << std::endl;
    std::cout << "checksum of 20209913 is " << add_checksum(20209913) << std::endl;
    std::cout << "checksum of 20224012 is " << add_checksum(20224012) << std::endl;
    //test array add checksum
    const std::size_t QTY_VALUES{3};
    unsigned int value_series[QTY_VALUES]{20201122, 0, 2022401200};
    add_checksum(value_series, QTY_VALUES);
    std::cout << "Series with checksums added: ";
    for (std::size_t series_index{0};
        //test removing checksum for arrays
         series_index < QTY_VALUES; series_index++)
    {
        std::cout << value_series[series_index] << " , ";;
    }    
    std::cout << std::endl;
    //test removing checksum for arrays
    std::cout << "Checksums removed: " << std::endl;
    remove_checksum(value_series, QTY_VALUES);
    for (std::size_t series_index{0};
         series_index < QTY_VALUES; series_index++)
    {
        std::cout <<  series_index<< "\t" << value_series[series_index] << std::endl;
    }
    std::cout << std::endl;
    return 0;

}
#endif
unsigned int add_checksum(unsigned int n)
{
    //if the number is more than 8 digits return max unsgined value
    if(n > 99999999) return UINT_MAX; 
    //this does not work in the digit-checking while loop so return 0
    if(n == 0) return 0;

    unsigned int store_n{n};
    unsigned int num_of_digits{};
    unsigned int nth_digit{};
    unsigned int digit_1{};
    unsigned int digit_2{};
    unsigned int double_nums_sum{};
    unsigned int nth_digits_sum{};
    unsigned int checksum{};
    unsigned int n_with_checksum{};
    //code for counting number of digits in n
    //stop at n = 0 because a number less than ten being divided by 10 gives 0 
    while(store_n != 0){
        store_n /= 10;
        ++num_of_digits;
    }
    //in the following for loop, n will be manipulated. Save its original value
    store_n = n;
    //moving from the right to the left of the integer, multiply every other digit by 2
    //starting from the rightmost being multiplied by 2.
    for(unsigned int k{1} ; k <= num_of_digits ; ++k)
    {
        //only perform operation on every other digit of the array
        if(k % 2 != 0)
        {
            //get the digit by cutting off the rest of n
            nth_digit = n%10;
            //truncate that digit from above off
            n /= 10;
            nth_digit *= 2;
            //if n is double digit
            if(nth_digit > 9)
            {
                digit_1 = nth_digit % 10;
                digit_2 = nth_digit / 10;
                double_nums_sum = digit_1 + digit_2;
                //now it is single-digit
                nth_digit = double_nums_sum;
            }
        //for the digits that do not get multiplied by 2
        } else {
            nth_digit = n%10;
            n /= 10;
        }
        //add this modified digit to the sum of all n's digits
        nth_digits_sum += nth_digit;
    }
    nth_digits_sum *= 9;
    checksum = nth_digits_sum % 10;
    //multiply n by 10 to shift all digits 1 place to the left
    //with the rightmost being 0
    store_n *= 10;
    //now it is 9 digits with rightmost digit being checksum 
    n_with_checksum = store_n + checksum;
    return n_with_checksum;
}
bool verify_checksum(unsigned int n) 
{
    //return false if n is more than 9 digits
    if(n > 999999999) return false;
    unsigned int checksum_value{};
    //the last digit of n (remainder) is our checksum
    checksum_value = n%10; 
    //get all digits except for the checksum
    n /= 10; 
    //call the add_checksum function and remove all digits
    //but the rightmost one, if that is equal to the checksum value
    //we calculated earlier then the number is correct
    if(add_checksum(n) % 10 == checksum_value) return true;
    //if we get here then the number is incorrect
    return false;
}
unsigned int remove_checksum(unsigned int n) {
    //if number is 10+ digits or invalid
    if(n > 999999999 || verify_checksum(n) == false) return UINT_MAX;
    //truncate last digit so total digits is 8
    return n/10;
}
void add_checksum(unsigned int array[], std::size_t capacity)
{
    //if the array is empty, return 
    if(capacity == 0) return;
    //go through every element and add the checksum value
    for (unsigned int k{} ; k < capacity; ++k)
    {
        array[k] = add_checksum(array[k]);
    }
}
void remove_checksum( unsigned int array[], std::size_t capacity )
{
    for (unsigned int k{} ; k < capacity; ++k)
    {
        array[k] = remove_checksum(array[k]);
    }
}