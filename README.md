# Cache-Simulator
Simulate the behavior of a cache
In this project, we are to simulate the behavior of a First In First Out (fifo), with either Direct, fully Associative, or partially Associative associativity to accept blocks from memory and store them accordingly. In addition, the user has an option to simulate this cache as either a non-prefetching or prefetching cache, with the latter storing the given address+block offset as the prefetched tag.

Program:
1. Given the cache size, block size, and type of associativity, we can determine:
  a. s, which is the number of sets in the cache, 
  b. a, which is the associativity (number of cache lines) for each set in the cache.  
  c. blockoff, the block offset in the address
  d. setoff, the set offset in the address

2. We use fscanf in a while loop to scan the input file for addresses until we hit the end of the inputted file. From here, we will perform operations on the address to determine its placement in the cache.
In the Loop:
WITHOUT PREFETCHING========================================================================
3. Cut off the block offset using bit shifting. address >> blockoff will provide the tag and the set bits. In this simulation we do not need to worry about the data itself so simply cutting off the blockoffset is fine.
4. Determine the set index, or the set number. We can do this using the equation setIndex=(address>>blockoff) && ((1<<setoff)-1) to isolate the set bits, giving use the setIndex. Afterwards, we can use address>>(blockoff+setoff) to leave us with only the tag.
At this juncture, we have:
  a. The tag
  b. The setIndex, or which set the tag belongs in
  c. The number of cache lines in each set
  
5. Given that this is a FIFO cache, we first need to set up a way to determine the oldest tag in any set. To do so,  we set up a counter which will increment by 1 each time the loop iterates, and is assigned to each new read address. In addition, a for loop is made to traverse the set determined by setIndex of the address, and then determine the oldest one using a comparison of the counter, or "age", of each tag stored. In this model, the tag with the greatest age will be the most recent, and the tag with the smallest age in the set will be the oldest - and in accordance with fifo will be removed from the set and replaced by the another tag if needed. This loop simply tells us the position of the cache line containing the oldest tag.
6. Now, we will enter a new for loop that will begin at the setIndex and traverse each cache line in the set. 
In this loop:
  a. We will first scan if the invalid bit of the address is 0. This is a miss, therefore we increment accordingly, and place the tag at the cache line in which the valid bit is 0, and make the valid bit 1, assign the counter to the age, and break the loop.
  b. We will then check if the tag matches another tag stored in the set, and if it does, it will be a hit, and we increment accordingly, and break the loop.
7. Outside of the for loop, an if statement checks if the loop has fully executed, meaning that neither of the two previous conditions broke the loop early, meaning that the tag has missed in a set which contains no invalid bits. Being a miss, we increment accordingly, and set the tag at the smallest, or oldest tag's location as previous calculated in step 5, and assigning the current counter to its age.
8.Now we output the information, ending the non prefetching cache.

WITH PREFETCHING==============================================================================

The general principle behind prefetching is almost the exact same as that without prefetching- basically if the tag results in a miss, the prefetching address, as described earlier, will be looked for in its own set corresponding to the prefetched address (prefadd). If it already exists, IT IS NOT A HIT, and does nothing. If it is not, it will load the new prefadd into the cache following the same principles as normal, and will count as a memory read. In implementation:

9. Because prefetching occurs where the cache will result in a miss, in this code this will occur twice. Therefore, in the if statement for determining if there is an invalid bit, when it evaluates to true and a miss occurs, create a copy of the original for loop to determine the oldest tag in the set, but this time apply it to the prefadd setIndex and determine the oldest block. Afterwards, follow the small pattern for the previous nonfetching cache to load and or not load depending on your cache.

