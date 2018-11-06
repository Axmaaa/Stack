// Comment next line to delete check correctness
#define CHECK_STACK_CORRECTNESS_
#ifdef CHECK_STACK_CORRECTNESS_
#define CHECK_STACK_CORRECTNESS
#else
#define CHECK_STACK_CORRECTNESS if(0)
#endif // CHECK_STACK_CORRECTNESS_

const int ERROR = 0xDEADBEEF;
const int STACK_STD_SIZE = 4;
const int STACK_MIN_SIZE = 2;
const int STACK_RESIZE_MULTIPLIER = 2;

typedef int sdata_t;

struct Stack
{
    int top;
    int capacity;
    sdata_t * data;
};


/**
    \brief Creates stack

    Creates stack and return stack pointer with zero data and STD_STACK_SIZE capacity

    \return Stack pointer
*/
struct Stack * StackCreate();


/**
    \brief Extends the stack

    Make the capacity of stack STACK_RESIZE_MULTIPLIER times more

    \param[in] s stack pointer

    \return 0 if all is OK
    \return ERROR if there is an error
*/
int StackExtension(struct Stack * s);


/**
    \brief Push element into stack

    \param[in] s srack pointer
    \param[in] n new data element

    \return 0 if all is OK
    \return ERROR if there is an error
*/
int StackPush(struct Stack * s, sdata_t n);


/**
    \brief Compresses the stack

    Make the capacity of stack STACK_RESIZE_MULTIPLIER less

    \param[in] s stack pointer

    \return 0 if all is OK
    \return ERROR if there is an error
*/
int StackCompression(struct Stack * s);


/**
    \brief Pop element from stack

    \param[in] s stack pointer

    \return Popped element if all is OK
    \return ERROR if there is an error
*/
sdata_t StackPop(struct Stack * s);


/**
    \brief Gives size of stack

    \param[in] s stack pointer

    \return Size of stack if all is OK
    \return -1 if something is wrong
*/
int StackGetSize(struct Stack * s);


/**
    \brief Check that stack is correct

    \param[in] s stack pointer

    \return 1 if stack is correct
    \return 0 if something is wrong
*/
int StackCorrectness(struct Stack * s);



/*****************************************************************************************************************************************************************************************************/



struct Stack * StackCreate()
{
    struct Stack * s = (struct Stack *)calloc(1, sizeof(struct Stack));
    if (s == NULL)
    {
        fprintf(stderr, "No memory for stack\n");
        return NULL;
    }
    s->data = (sdata_t *)calloc(STACK_STD_SIZE, sizeof(sdata_t));
    s->capacity = STACK_STD_SIZE;
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return NULL;
    return s;
}


int StackExtension(struct Stack * s)
{
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return ERROR;
    if (s->top < s->capacity)
    {
        fprintf(stderr, "Stack needn't to be extendedn\n");
        return ERROR;
    }
    sdata_t * tmp = s->data;
    s->data = (sdata_t *)calloc(s->capacity * STACK_RESIZE_MULTIPLIER, sizeof(sdata_t));
    s->capacity *= STACK_RESIZE_MULTIPLIER;
    for (int i = 0; i < s->top; i++)
    {
        s->data[i] = tmp[i];
    }
    free(tmp);
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return ERROR;
    return 0;
}


int StackPush(struct Stack * s, sdata_t n)
{
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return ERROR;
    if (s->top >= s->capacity)
    {
        if (StackExtension(s) == ERROR)
        {
            fprintf(stderr, "I can't increase the stack\n");
            return ERROR;
        }
    }
    s->data[s->top] = n;
    s->top++;
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return ERROR;
    return 0;
}


int StackCompression(struct Stack * s)
{
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return ERROR;
    if (s->top >= (s->capacity / STACK_RESIZE_MULTIPLIER - 1) || (s->capacity / STACK_RESIZE_MULTIPLIER <= STACK_MIN_SIZE))
    {
        fprintf(stderr, "Stack shouldn't to be compressed\n");
        return ERROR;
    }
    sdata_t * tmp = s->data;
    s->data = (sdata_t *)calloc(s->capacity / STACK_RESIZE_MULTIPLIER, sizeof(sdata_t));
    s->capacity /= STACK_RESIZE_MULTIPLIER;
    for (int i = 0; i < s->capacity; i++)
    {
        s->data[i] = tmp[i];
    }
    free(tmp);
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return ERROR;
    return 0;
}


sdata_t StackPop(struct Stack * s)
{
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return ERROR;
    sdata_t tmp = s->data[s->top - 1];
    s->data[s->top] = 0;
    s->top--;
    if ((s->top < (s->capacity / STACK_RESIZE_MULTIPLIER - 1)) && (s->capacity / STACK_RESIZE_MULTIPLIER > STACK_MIN_SIZE))
    {
        StackCompression(s);
    }
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return ERROR;
    return tmp;
}


int StackGetSize(struct Stack * s)
{
    CHECK_STACK_CORRECTNESS if (StackCorrectness(s) == 0) return -1;
    return s->top;
}


int StackCorrectness(struct Stack * s)
{
    if (s == NULL)
    {
        fprintf(stderr, "Stack nullptr\n");
        return 0;
    }
    if (s->data == NULL)
    {
        fprintf(stderr, "Data nullptr\n");
        return 0;
    }
    if (s->capacity <= 0)
    {
        fprintf(stderr, "Capacity is less or equal zero\n");
        return 0;
    }
    if (s->top > s->capacity)
    {
        fprintf(stderr, "Stack size is greater than capacity\n");
        return 0;
    }
    if (s->top < 0)
    {
        fprintf(stderr, "Stack size is less than 0\n");
        return 0;
    }
    return 1;
}
