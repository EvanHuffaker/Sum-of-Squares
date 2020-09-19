#include "squareSum.h"

#define SQUARE(x) (x) * (x)

#define printFunc putchar('(');         \
    for(i = 0; i < maxnums; i++) {      \
        printf("%u",nums[i]);           \
        if(i < maxnums - 1) {           \
            putchar(',');               \
            }                           \
        }                               \
        printf("): %u\n",a);


#if MAXNUMS < 0
#error "MAXNUMS must be possitive.\n"
#endif

/**
 * @headerfile none
 * @private
 * @author Evan Huffaker
 *
 * @brief This function sets each value in nums to 0.
 *
 * @details This function sets each value in nums to 0.  It is only used in the solve function, before the loop.  Since
 * it is only called once, it does not need to be made efficient, and therefore can be made into its own function to
 * reduce bulk in the solving function.
 * @param MAXNUMS This is the number of positions within nums
 * @param nums This is the array of numbers in calculating the sum of squares.
 */
void init(unsigned maxnums, unsigned nums[maxnums]) {
    unsigned i;
    for(i = 0; i < maxnums; i++) {
        nums[i] = 0;
    }
}


/**
 * @headerfile squareSum.h
 * @public
 * @author Evan Huffaker
 * @brief This function solves for the square root of the sum of squares.  It prints any integer number combination up
 * to a given value.  The number of squares is also given as an argument.
 *
 * @details This function is broken into the initialization part and the loop part.
 * The initialization part occurs before the loop, and it allocates memory for each variable used, and initializes each
 * value in nums to 0.  Since this part is only used once, it does not need to be made that efficient.
 *
 * The loop part is broken further into two sections: the first for incrementing nums and the last for finding the square
 * root of the sum of squares.
 *
 * The incrementing part of the loop performs two things: it increments nums and it calculates the sum of squares.  To
 * increment, it starts with the first value in nums, increments it, then tests to see if it is greater than the next
 * value in nums.  If it is, it resets the current value in nums to 0, and tries again for the next value until no carry
 * occurs.  To calculate the sum of squares, it starts where the increment loop left off, because 0 does not change the
 * sum.  It uses a local macro to calculate the square of a number.
 *
 * The square root part of the loop is further broken into two parts.  The first is if in incrementing nums, a carry did
 * occur.  The next is if carry did not occur.  If carrying did not occur, then the square root of the sum of squares
 * must be either the previous square root, or 1 over.  It then tests for equality.  However, if carrying did not occur,
 * the function finds the min and max values the square root could be, which is the max value in nums and the sum of each
 * value in nums, respectively.  It narrows the min and max window as it approaches the final square root.
 *
 * @param MAXL This is the maximum value of each element in the array nums (local variable.)
 * @param numbers This is the number of values in the sum of squares
 *
 * @var nums This is an array which is used to store each number to be squared and added.
 * @var a2 This is the sum of squares, the dot product of nums by itself
 * @var a This is the square root of a2 (integer square root.)
 * @var a1 This is the previous value of a.  The value is used to help calculate the square root of a2 if nums was not
 * carried (sum of each element in nums increases)
 * @var didCarry This is a flag, which is true if nums was carried in its increment.  In other words, if the previous
 * sum of each element in nums is less than the current sum, then didCarry will be false.
 * @var sum This is the sum of each element in nums.  It is only calculated if didCarry is true, and is the upper bound
 * for the square root of a.
 * @var a10 This is the square of a1.  It is used when didCarry is false, it is used.
 * @var min This is the minimum value for the square root.  It starts as the maximum value in nums
 * @var guess This is the square of a value tested to be the square root.
 *
 */
void solve(unsigned MAXL, unsigned numbers) {
    unsigned maxnums = numbers;                                 // This must be declared first to allocate space for nums
    unsigned nums[maxnums], a2, a, a1, i, sum, a10, min, guess; // see doxygen comments for variable details
    unsigned char didCarry;


    init(maxnums, nums);        // this line initializes each value in nums to 0

    a10 = a = a1 = 0;

    while(nums[maxnums - 1] <= MAXL) {
        didCarry = 0;
        a2 = 0;

        /*
         * This section increments nums by 1, and partially calculates a^2
         * Incrementing algorithm:
         *      - increment the first value in nums
         *      - if the value is greater than the next, reset current value to 0 and set carry flag
         *      - try incrementing for the next value.  Repeat until done.
         *
         */
        for(i = 0; i < maxnums; i++) {
            nums[i]++;
            if(i != (maxnums - 1) && nums[i] > nums[i + 1]) {
                nums[i] = 0;                                    // resets current nums value
                didCarry = 1;                                   // assigns carry flag
                continue;                                       // skips to the next value in nums
            }
            break;  // break if no more carrying
        }

        /*
         * Ths for loop calculates a2 from the first position in nums not 0.
         */
        for(; i < maxnums; i++) {
            a2 += SQUARE(nums[i]);
        }

        /*
         * This part of the function calculates the square root of the sum of squares.
         * Important variables here:
         *          - didCarry: This is a flag, which is 1 if, when generating the current number, some sort of carrying between values of nums happened.
         *          - a:        This is the square root of the sum of squares.
         *          - a1:       This is the previous 'a' value.
         *          - a10:      This is the equivalent to a1 * a1
         *          - sum:      This is the sum of each value in nums, but is also the maximum value the square root can be.
         *          - min:      This is the minimum value the square root can be, the maximum value in nums.
         *
         * Important macros used:
         *          -calSumNum: This calculates the sum of each element in nums and assigns it to the variable 'sum.'
         *          - SQUARE:   This calculates the square of a number.
         *
         * Square root algorithms:
         *          - if(didCarry):
         *                  * calculate the square root based on the upper and lower bound possibilities.
         *                  * The lower bound that the square root could be is the maximum value in nums, which is always the last element.
         *                  * The upper bound that the square root could be is the sum of each value in nums (Parseval Identity).
         *          - else:
         *                  * The previous square root should be, or close to the current square root value.
         *                  * First checks if the previous square root value, squared, is the current sum of squares value
         *                  * If it is not, then it adds 1 to the previous square root value, and tries again.
         *                          # It is impossible for an infinite loop to occur here because a10 will eventually grow bigger than a2
         */
        if(didCarry) {
            sum=0;
            // This for loop sums each element in nums, setting the upper bound to the square root.
            for(i=0; i < maxnums; i++){
                sum+=nums[i];
            }

            /*
             * This line calculates the square root of a2, which is somewhere between the maximum value in nums and the
             * sum of each element in nums.
             */
            min = nums[maxnums - 1];
            while(1) {
                a = (min + sum) >> 1u;
                guess = SQUARE(a);
                if(guess == a2 || sum - min < 2)
                    break;
                else if(guess > a2)
                    sum = a;
                else if(guess < a2)
                    min = a;
            }

            a1 = a;                         // assigning the current value of a to the previous value in case the next iteration of nums does not carry.
            a10 = SQUARE(a1);               // calculates a1 * a1 for future uses
            if(a10 != a2) {                 // if the square root of the sum of squares is not an integer, try next number
                continue;
            }
            else {                          // if the square root of the sum of squares is an integer, print!
                printFunc;
            }
        }

        /*
         * If nums was not carried, then a must be less than 1 off from a1.  Therefore, can check if a1^2 is equal to a2,
         * or (a1+1)^2 is equal to a2.
         * This whole part is so simplistic because nums is only incremented by 1, and the sum of squares remains almost the same.
         */
        else {
            sqrtLabel:                  // see "else if(a10 < a2) {...}
            if(a10 == a2) {             // if the square of a0 is equal to the sum of squares (a1 must be the square root of the sum of squares)
                a = a1;                 // only passes if a1 is the square root (exactly) of a2
                printFunc;
            }
            else if(a10 < a2) {         // if the square of a0 is less than the sum of squares
                a1++;                   // adjust a1 by 1
                a10 = SQUARE(a1);       // recalculate a10
                goto sqrtLabel;         // jumps back to top of if else chain, allowing fast, semi-recursive functionality without arguments.
            }
        }

    }

}