/**
 * How to start using Big(O) to understand Algorithms
 */
/**
 * We’ve all heard of Big(O).
 * It’s something most of us
 * learn in college and promptly
 * forget. We also know it’s
 * something that Top Coders and
 * Googlers are good at and many
 * of us would like to be good
 * at it too!
 */
/**
 * Big-O.png
 */
/**
 * I can relate – I find many
 * algorithms fascinating and
 * many more intimidating. And
 * for a long time I struggled
 * to get my head around the
 * concept of Big(O). I knew
 * what it was – vaguely – but I
 * had no deep understanding –
 * no intuition for it at all.
 * And I knew that it was
 * important in telling me which
 * algorithms were good and
 * which weren't.
 *
 * If you can relate to that
 * feeling then this article is
 * for you – you will be able to
 * _understand_ Big(O) and have
 * the beginnings of an
 * intuition about it.
 *
 * As always, this blog post is
 * also a fully executable
 * program - this time you can
 * use it to play with the
 * various Big(O) algorithms and
 * develop a feel for how they
 * react to different inputs.
 */
/**
 * *_What _is_ Big(O) anyway?_*
 */
/**
 * So what is Big(O)? The
 * easiest way to understand it
 * is - Big(O) just describes
 * how any algorithm scales up.
 *
 * How does it do this? It
 * simply focuses on the
 * upper-limit on the algorithm
 * ignoring all exceptions,
 * special cases, and complex
 * details and irrelevant
 * constants.
 *
 * So when you want to know how
 * a bit of code is going to
 * handle more and more inputs -
 * just figure out it's Big(O).
 */

/**
 * *_How do we find the Big(O)?_*
 */
/**
 * Finding the Big(O) is
 * surprisingly easy! Just
 * "squint" at your algorithm -
 * ignore the details - find the
 * main repetitions (the
 * loops/recursions) and you've
 * trapped the Big(O).
 *
 * Let's try it out:
 *
 * Example 1:
 * ----------
 *  for(item in haystack) {
 *      if(item == needle) return item;
 *  }
 *
 * Here is a simple loop that
 * walks through every single
 * input once. Therefore for `n`
 * inputs it performs `n`
 * repetitions giving us:
 *  O(n)
 *
 *
 * Example 2:
 * ----------
 *  low = 0;
 *  high = sortedhaystack.size - 1;
 *  while(low <= high) {
 *      mid = (low+high)/2;
 *      item = sortedhaystack[mid];
 *      if(item == needle) return item;
 *      if(item < needle) low = mid+1;
 *      else high = mid - 1;
 *  }
 *
 * Squinting at this algorithm
 * we see:
 *  ...
 *  while(low <= high) {
 *      ...
 *      mid = (low+high)/2;
 *      if() low = mid;
 *      else high= mid;
 *      ...
 *  }
 * We again start of with the
 * entire range of inputs but
 * each repetition _halves_ the
 * range it has to travel by
 * narrowing to the mid point.
 * This kind of discarding half
 * a range is terribly common
 * and terribly useful. Such a
 * constant halving means that
 * each repetition shrinks
 * to log(n) items. Therefore we
 * say this algorithm has:
 *  O(log(n))
 *
 * Because this is common it is
 * useful to keep in mind the
 * relation between discarding
 * chunks of input and _log(n)_.
 */
/**
 * *_Why does this matter?_*
 */
/**
 * So now we've found the
 * Big(O)! Big deal! How does
 * that help us know which
 * algorithm is better?
 *
 * Well remember, Big(O) gives
 * us useful information as the
 * algorithm scales. If we have
 * a small haystack then it
 * really doesn’t matter – even
 * if each loop takes a second
 * then a haystack of a few
 * hundred items will finish
 * quickly enough in both cases.
 *
 * But if we have a million
 * items things get interesting:
 *
 * Algorithm 1: (1 second per loop)
 *  O(n) = O(1,000,000)
 *       ~> 1,000,000 seconds
 *       = 11 days to complete
 *
 * Algorithm 2: (1 second per loop)
 *  O(log(n)) = O(log(1,000,000))
 *            = O(19.93)
 *            ~> 19.93 seconds
 *            = 20 seconds to complete
 *
 * We can now see there is a
 * _phenomenal_ difference
 * between the two. Just knowing
 * the Big(O) can really help
 * us!
 */
/**
 * *_Meet the Big(O) classes_*
 */
/**
 * What really makes Big(O)
 * useful is that most
 * algorithms fall within a few
 * Big(O) clases. Once we know
 * them and how they scale, we
 * can quickly estimate how
 * almost any algorithm scales.
 *
 * Let's look at the important
 * Big(O) classes now.
 */
/**
 * big-o-summary-small.png [href=007/big-o-summary.png]
 */
/**
 * Taking each in turn, let's
 * look at the important
 * characteristics and try and
 * build an inutition for each
 * along with an actual working
 * algorithm below:
 */

/* (Some setup) */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

enum OClass {
    O1,
    O_logn,
    O_sqrtn,
    O_n,
    O_nlogn,
    O_n_power_2,
    O_2_power_n,
    O_n_permut,
    O_n_power_n,
};

#define UNUSED(x) (void)(x)
#ifdef DUMP_RESULT
    #define RESULT(x) printf("%s\n",#x)
#else
    static long _dummy;
    #define RESULT(x) (_dummy=1)
#endif

/* The environment ties
 * the algorithms, their
 * descriptions, and their data.
 */
typedef void (*func)(void* data);
struct environment {
    long n;
    func algo;
    void *data;
    enum OClass oclass;
};

struct array {
    long sz;
    int *vals;
};

struct search {
    int needle;
    struct array *haystack;
};

struct range_sum {
    long *slice_sum;
    long root_sz;
    long from;
    long to;
    struct array *array;
};

/**
 * flash.png
 */
/**
 * *_O(1): Flash - The Fastest O_*
 *
 * This is the *Holy Grail* - an
 * algorithm that always
 * completes in a fixed time
 * irrespective of the size of
 * the input.
 *
 * *__Completes 1 Million items
 * in:
 *      1 second
 * .__*
 *
 * Examples:
 * return the head of a list,
 * insert a node into a linked
 * list, pushing/popping a
 * stack, inserting/removing
 * from a queue,...
 */
void get_first(struct array* array) {
    if(array->sz > 0) RESULT(array->vals[0]);
    else RESULT(-1);
}

/**
 * shrinking-violet.png
 */
/**
 * *_O(log(n)): Shrinking Violet - Divide and Conquer_*
 *
 * These algorithms never have
 * to look at all the input.
 * They often halve inputs at
 * each stage and thus have
 * inverse the performance of
 * the higher powers (see the
 * Power-Sisters to contrast).
 *
 * *__Completes 1 Million items
 * in:
 *      20 seconds
 * .__*
 *
 * Examples:
 * looking up a number in a
 * phone book, looking up a word
 * in a dictionary, doing a
 * binary search, find element
 * in a binary search tree,
 * deleting from a doubly-linked
 * list,...
 */
void binary_jump_search(struct search *s) {
    long jump = s->haystack->sz / 2;
    long pos = 0;

    while(jump > 0) {
        while(pos + jump < s->haystack->sz && s->haystack->vals[pos+jump] <= s->needle) pos+=jump;
        jump = jump / 2;
    }
    if(s->haystack->vals[pos] == s->needle) RESULT("Found needle!");
    else RESULT("Needle not found!");
}

/**
 * groot.png
 */
/**
 * *_O(√n): Groot - The Rare O_*
 *
 * If we notice:
 *                n
 *  sqrt(n) = ---------
 *             sqrt(n)
 *
 * in some sense, √n is in the
 * "middle" of `n`. This type of
 * algorithm is not very
 * commonly found.
 *
 * *__Completes 1 Million items
 * in:
 *      16 minutes
 * .__*
 *
 * Examples:
 *  Grover’s algorithm,
 *  [href=http://www.infoarena.ro/blog/square-root-trick](the square root trick)
 */
void range_sum_query(struct range_sum* rs) {
    long sum = 0;
    int i = rs->from;
    while((i+1)%rs->root_sz != 0 && i <= rs->to) {
        sum += rs->array->vals[i++];
    }
    while(i + rs->root_sz <= rs->to) {
        sum += rs->slice_sum[i/rs->root_sz];
        i += rs->root_sz;
    }
    while(i <= rs->to) {
        sum += rs->array->vals[i++];
    }
    RESULT(sum);
}
void setup_slice_sums(struct range_sum* rs) {
    int i;

    rs->root_sz = (long)sqrt(rs->array->sz);

    int max_slice = rs->array->sz/rs->root_sz;
    int num_slices = max_slice + 1;

    rs->slice_sum = malloc(sizeof(long)*num_slices);
    for(i = 0;i < num_slices;i++) {
        rs->slice_sum[i] = 0;
    }
    for(i = 0;i < rs->array->sz;i++) {
        rs->slice_sum[i/rs->root_sz] += rs->array->vals[i];
    }
}

/**
 * clark-kent.png
 */
/**
 * *_O(n): Clark Kent - Just a Straight guy_*
 *
 * These are _linear_ algorithms
 * which scale directly
 * proportional to the input.
 * This is commonly the case
 * because we often have to
 * access an item at least once.
 *
 * *__Completes 1 Million items
 * in:
 *      11 days
 * .__*
 *
 * Examples:
 * finding the maximum/minimum
 * of a collection, finding the
 * max sequential sum,
 * traversing a linked list,
 * deleting from a singly-linked
 * list,...
 */
void linear_search(struct search *s) {
    int i;

    for(i = 0;i < s->haystack->sz;i++) {
        if(s->haystack->vals[i] == s->needle) {
            RESULT("Found needle!");
            return;
        }
    }
    RESULT("Needle Not Found!");
}

/**
 * hisoka.png
 */
/**
 * *_O(nlog(n)): Hisoka - Sorting Cards_*
 *
 * Sorting is pretty useful for
 * many, many, things. When
 * sorting we need to compare
 * each of the items with each
 * other. The cleverest sorting
 * algorithms compare each item
 * with an ever reducing set of
 * other items and are therefore
 *
 *  O( n   log(n)   )
 *     ^     ^
 *     |     L with a reducing(log!)
 *  Compare     set
 *  each item
 *
 * It can be shown that
 * algorithms that need to
 * compare elements cannot sort
 * faster than this (Algorithms
 * like counting sort and radix
 * sort use other information
 * and can be faster).
 *
 * *__Completes 1 Million items
 * in:
 *      ~ 1 year!
 * .__*
 *
 * Examples:
 * Merge Sort, Quick Sort, Heap Sort...
 */
long partition_1(int* array, long low, long high) {
    long left = low;
    long right = high;
    long pivot = array[low];

    while(left < right) {
        while(array[left] <= pivot && left <= high) left++;
        while(array[right] > pivot) right--;
        if(left < right) {
            int tmp;
            tmp = array[left];
            array[left] = array[right];
            array[right] = tmp;
        }
    }
    array[low] = array[right];
    array[right] = pivot;

    return right;
}
void quick_sort_1(int* array, long low, long high) {
    long pivot;
    if(low < high) {
        pivot = partition_1(array, low, high);
        quick_sort_1(array, low, pivot-1);
        quick_sort_1(array, pivot+1, high);
    }
}
void quick_sort(struct array *array) {
    quick_sort_1(array->vals, 0, array->sz-1);
}

/**
 * power-sisters.png
 */
/**
 * *_O(n^2),O(n^3): The Power Sister - Growing Polynomially*
 *
 * These algorithms grow as a
 * polynomial of the input.
 * O(n^2) are known as Quadratic
 * and are known as Cubic
 * algorithms. Higher powers
 * are just known as bad
 * algorithms :-)
 *
 * The powers usually reflect
 * the number of nested loops in
 * the system.
 *
 * *__Completes 1 Million items
 * in:
 *      O(n^2) ~> 32,000 years
 *      O(n^3) ~> 32,000,000,000 years
 * .__*
 *
 * *NB*: This brings up a *VERY*
 * important point about Big(O) -
 * whenever there are multiple
 * Big-O’s in an algorithm, the
 * biggest class wins out
 * because it dominates the
 * scaling. We can see this by
 * noticing the time that
 * smaller classes take in
 * comparison with larger
 * classes we have seen so far.
 *
 * Examples:
 * O(n^2) - multiplying two
 * n-digit numbers by a simple
 * algorithm, adding two n×n
 * matrices, bubble sort,
 * insertion sort, number of
 * handshakes in a room,...
 * O(n^3) - multiplying two n×n
 * matrices by a naive
 * algorithm,...
 */
void find_max_seq_sum(struct array* array) {
    double max_sum = 0;
    int i,j;

    for(i = 0;i < array->sz;i++) {
        double curr_sum = 0;
        for(j = i;j < array->sz;j++) {
            curr_sum += array->vals[j];
            if(curr_sum > max_sum) max_sum = curr_sum;
        }
    }
    RESULT(max_sum);
}

/**
 * wonder-woman.png
 */
/**
 * *_O(2^n): Wonder Woman - Combination Loops_*
 *
 * These are exponential
 * algorithms whose growth
 * doubles with every new
 * addition to the input.
 *
 * You can recognize these as
 * recursive algorithms that
 * solve a problem of size `n`
 * by recursively solving two
 * problems of size `n-1`.
 *
 * Another such type is one that
 * iterates over all subsets of
 * a set. If you find it hard to
 * understand how iterating over
 * subsets translates to,
 * imagine a set of switches,
 * each of them corresponding to
 * one element of a set. Now,
 * each of the switches can be
 * turned on or off. Think of
 * "on" as being in the subset
 * and "off" being not included.
 * Now it should be obvious that
 * there are  combinations.
 *
 * *__Completes 1 Million items
 * in:
 *      3.2x10^301019 Millennia!!
 * .__*
 *
 * Examples:
 * Tower of Hanoi, Naive
 * Finonacci Calculation,...
 */
void solve_hanoi_1(long num, int from_peg, int to_peg, int spare_peg) {
    if(num < 1) return;
    if(num > 1) solve_hanoi_1(num-1, from_peg, spare_peg, to_peg);
    RESULT("move remaining one from_peg -> to_peg");
    if(num > 1) solve_hanoi_1(num-1, spare_peg, to_peg, from_peg);
}
void solve_hanoi(int num) {
    solve_hanoi_1(num, 1, 2, 3);
}

/**
 * link.png
 */
/**
 * *_O(n!): Link - The Traveling Salesman_*
 *
 * These algorithms iterate over
 * all possible combination of
 * inputs.
 *
 * *__Completes 1 Million items
 * in:
 *      2.7x10^5565698 Millennia
 *      (good grief!!!)
 * .__*
 *
 * Examples:
 * The traveling salesman
 * problem,...
 */
/**
 * black-panther.png
 */
/**
 * *_O(n^n): The Blackest Panther - The Slowest O_*
 *
 * This is just included for
 * fun. Such an algorithm will
 * not scale in any useful way
 * and I don't know of any.
 *
 * Examples:
 * Please don't find any!
 *
 * Did this help you understand
 * Big-O better? Which is your
 * favourite Big-O class? Let me
 * know what you think!
 *
 */


/* (actually run algos and show results) */

char* oclass_1_str(enum OClass oclass) {
    switch(oclass) {
        case O1: return "O(1)";
        case O_logn: return "O(log(n))";
        case O_sqrtn: return "O(sqrt(n))";
        case O_n: return "O(n)";
        case O_nlogn: return "O(n log(n))";
        case O_n_power_2: return "O(n^2)";
        case O_2_power_n: return "O(2^n)";
        case O_n_permut: return "O(n!)";
        case O_n_power_n: return "O(n^n)";
        default: return "ERROR!";
    }
}
void show_time_msg_1(clock_t begin, clock_t end) {
    printf("%lf", (double)(end - begin));
}
void show_time_taken(struct environment* environment) {
    clock_t begin,end;

    if(!environment->data) {
        printf("%-12s(%ld items): (Not executed)\n",
            oclass_1_str(environment->oclass),
            environment->n);
        return;
    }

    printf("%-12s(%ld items): ",
            oclass_1_str(environment->oclass),
            environment->n);
    fflush(stdout);

    begin = clock();
    environment->algo(environment->data);
    end = clock();

    show_time_msg_1(begin, end);
    printf("\n");
}

/* [=] Show results of running
 * all algos in their
 * environments.
 */
void show_algo_results(struct environment* environments) {
    while(environments->algo) {
        show_time_taken(environments);
        environments++;
    }
}

/* [=] Return a large, random
 * array
 */
int* create_int_array(long sz) {
    long i;
    int *array = malloc(sz*sizeof(int));
    for(i = 0;i < sz;i++) {
        array[i] = rand();
    }
    return array;
}

/* [=] dummy function
 * for not implemented
 * algorithms.
 */
void do_nothing(void* data) {
}

/* [=] Setup the environment for
 * various algorithms
 */
struct environment* create_environments(long sz) {
    int i = 0;

    time_t t;
    srand((unsigned) time(&t));

    /* Setup a large block of
     * enviroments.
     * NB: if the number of
     * algo's > 100 this should
     * be changed
     */
    struct environment *environments = malloc(sizeof(struct environment)*100);
    struct environment *environment;

    /* setup data */
    struct array *sorted_array = malloc(sizeof(struct array));
    sorted_array->sz = sz;
    sorted_array->vals = create_int_array(sorted_array->sz);
    quick_sort(sorted_array);

    struct array *array = malloc(sizeof(struct array));
    array->sz = sz;
    array->vals = create_int_array(array->sz);

    struct array *mutable_array = malloc(sizeof(struct array));
    mutable_array->sz = sz;
    mutable_array->vals = create_int_array(mutable_array->sz);

    struct search *search = malloc(sizeof(struct search));
    search->haystack = sorted_array;
    search->needle = sorted_array->vals[rand()%(sorted_array->sz)];

    struct range_sum *rs = malloc(sizeof(struct range_sum));
    rs->array = array;
    setup_slice_sums(rs);
    rs->from = rand()%(rs->array->sz);
    rs->to = rand()%(rs->array->sz);
    while(rs->from < rs->to) {
        rs->from = rand()%(rs->array->sz);
        rs->to = rand()%(rs->array->sz);
    }

    /* O(1) */
    environment = &(environments[i++]);
    environment->n = array->sz;
    environment->algo = (func)&get_first;
    environment->data = array;
    environment->oclass = O1;
    /* O(log(n)) */
    environment = &(environments[i++]);
    environment->n = search->haystack->sz;
    environment->algo = (func)&binary_jump_search;
    environment->data = search;
    environment->oclass = O_logn;
    /* O(sqrt(n)) */
    environment = &(environments[i++]);
    environment->n = rs->array->sz;
    environment->algo = (func)&range_sum_query;
    environment->data = rs;
    environment->oclass = O_sqrtn;
    /* O(n) */
    environment = &(environments[i++]);
    environment->n = search->haystack->sz;
    environment->algo = (func)&linear_search;
    environment->data = search;
    environment->oclass = O_n;
    /* O(nlog(n)) */
    environment = &(environments[i++]);
    environment->n = mutable_array->sz;
    environment->algo = (func)&quick_sort;
    environment->data = mutable_array;
    environment->oclass = O_nlogn;
    /* O(n^2) */
    environment = &(environments[i++]);
    environment->n = array->sz;
    environment->algo = (func)&find_max_seq_sum;
    environment->data = array;
    environment->oclass = O_n_power_2;
    /* O(2^n) */
    environment = &(environments[i++]);
    environment->n = sz;
    environment->algo = (func)&solve_hanoi;
    environment->data = (void*)sz;
    environment->oclass = O_2_power_n;
    /* O(n!) */
    environment = &(environments[i++]);
    environment->n = sz;
    environment->algo = (func)do_nothing;
    environment->data = NULL;
    environment->oclass = O_n_permut;
    /* O(n^n) */
    environment = &(environments[i++]);
    environment->n = sz;
    environment->algo = (func)do_nothing;
    environment->data = NULL;
    environment->oclass = O_n_power_n;


    /* - end marker */
    environment = &(environments[i++]);
    environment->algo = NULL;

    return environments;
}

long get_sz(int argc, char* argv[]) {
    if(argc < 2) return 0;
    return atol(argv[1]);
}

int main(int argc, char* argv[]) {
    long sz = get_sz(argc, argv);
    if(!sz) printf("Usage: %s <number of items>\n", argv[0]);
    else show_algo_results(create_environments(sz));
}

