#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdalign.h>

#define var     __auto_type

#define MAX_ARGUMENT_LENGTH     2047

enum PARSE_PHASE_STATUS
{
    PARSE_PHASE_STATUS_LEFT_OPERAND = 0,
    PARSE_PHASE_STATUS_RIGHT_OPERAND,
    PARSE_PHASE_STATUS_LEFT_PARENTHESIS,
    PARSE_PHASE_STATUS_NEED_OPERATOR = 4,
    PARSE_PHASE_STATUS_HAS_NEG = 8
};

enum OPERATOR_PRIORITY
{
    OPERATOR_PRIORITY_ADD,
    OPERATOR_PRIORITY_MUL,
    OPERATOR_PRIORITY_POW
};

static inline bool IsDigital(char ch)
{
    return ch >= '0' && ch <= '9';
}

static inline int IsMathConstant(const char *cursor)
{
    if(cursor[0] == 'p' && cursor[1] == 'i')
        return 2;
    if(cursor[0] == 'e' && cursor[1] != 'x')
        return 1;
    return 0;
}

static inline bool IsMathFunction(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

static double ParseDigital(const char *cursor, int *pRetLength)
{
    var length = IsMathConstant(cursor);
    if(length > 0)
    {
        *pRetLength = length;
        return (cursor[0] == 'p')? M_PI : M_E;
    }
    
    char value[MAX_ARGUMENT_LENGTH + 1];
    
    char ch;
    var index = 0;
    var hasDot = false;
    
    do
    {
        ch = cursor[index];
        if(ch == '.')
        {
            if(hasDot)
                break;
            else
            {
                hasDot = true;
                value[index] = ch;
            }
        }
        else if(!IsDigital(ch))
            break;
        
        value[index++] = ch;
    }
    while(ch != '\0');
    
    value[index] = '\0';
    
    *pRetLength = index;
    
    return atof(value);
}

static double AddOp(double a, double b)
{
    return a + b;
}

static double MinusOp(double a, double b)
{
    return a - b;
}

static double MulOp(double a, double b)
{
    return a * b;
}

static double DivOp(double a, double b)
{
    return a / b;
}

static double ModOp(double a, double b)
{
    return (int64_t)a % (int64_t)b;
}

static double (* const opFuncTables[])(double, double) = {
    ['%' - '%'] = &ModOp,
    ['*' - '%'] = &MulOp,
    ['+' - '%'] = &AddOp,
    ['-' - '%'] = &MinusOp,
    ['/' - '%'] = &DivOp,
    ['^' - '%'] = &pow
};

static inline bool IsOperator(char ch)
{
    return (ch >= '%' && ch <= '/') || ch == '^';
}

static double radian(double degree)
{
    return degree * M_PI / 180.0;
}

static double degree(double radian)
{
    return radian * 180.0 / M_PI;
}

static double cot(double radian)
{
    return tan(M_PI * 0.5 - radian);
}

static double recp(double x)
{
    return 1.0 / x;
}

static const struct
{
    int name;
    double (*pFunc)(double);
} mathFuncList[] = {
    { '\0nis', &sin },
    { '\0soc', &cos },
    { '\0nat', &tan },
    { '\0toc', &cot },
    { 'hnis', &sinh },
    { 'hsoc', &cosh },
    { 'hnat', &tanh },
    { 'nisa', &asin },
    { 'soca', &acos },
    { 'nata', &atan },
    { 'hnsa', &asinh },
    { 'hsca', &acosh },
    { '\0gol', &log2 },
    { '\0\0gl', &log10 },
    { '\0\0nl', &log },
    { 'trqs', &sqrt },
    { 'trbc', cbrt },
    { 'pcer', &recp },
    { '\0dar', &radian },
    { '\0ged', &degree },
    { '\0pxe', &exp }
};

static double (*ParseMathFunction(const char *cursor, int *pLength))(double)
{
    char alignas(4) buffer[8] = { '\0' };
    var index = 0;
    
    for(var count = 0; count < 4; count++, index++)
    {
        var ch = cursor[index];
        if(!IsMathFunction(ch))
            break;
        
        buffer[index] = ch;
    }
    buffer[index] = '\0';
    
    var value = *(int*)buffer;
    
    const var length = sizeof(mathFuncList) / sizeof(mathFuncList[0]);
    for(typeof(length + 0) i = 0; i < length; i++)
    {
        if(mathFuncList[i].name == value)
        {
            *pLength = index;
            return mathFuncList[i].pFunc;
        }
    }
    
    return NULL;
}

static double ParseArithmeticExpression(const char **ppCursor, double leftOperand, enum PARSE_PHASE_STATUS status, enum OPERATOR_PRIORITY priority, bool *pStatus)
{
    const char *cursor = *ppCursor;
    var rightOperand = 0.0;
    
    var length = 0;
    
    double (*pOpFunc)(double, double) = NULL;
    
    double (*pMathFunc)(double) = NULL;
    
    bool isSuccessful = true;
    
    char ch;
    
    do
    {
        ch = *cursor;
        
        if(IsDigital(ch) || IsMathConstant(cursor) > 0)
        {
            double value = ParseDigital(cursor, &length);
            cursor += length;
            
            if((status & PARSE_PHASE_STATUS_RIGHT_OPERAND) == PARSE_PHASE_STATUS_LEFT_OPERAND)
            {
                leftOperand = value;
                if((status & PARSE_PHASE_STATUS_HAS_NEG) != 0)
                    leftOperand = -leftOperand;
            }
            else
            {
                rightOperand = value;
                if((status & PARSE_PHASE_STATUS_HAS_NEG) != 0)
                    rightOperand = -rightOperand;
            }
            
            status &= ~PARSE_PHASE_STATUS_HAS_NEG;
            
            status |= PARSE_PHASE_STATUS_NEED_OPERATOR;
        }
        else if(IsMathFunction(ch))
        {
            pMathFunc = ParseMathFunction(cursor, &length);
            if(pMathFunc == NULL)
            {
                isSuccessful = false;
                break;
            }
            cursor += length;
            if(*cursor != '(')
            {
                isSuccessful = false;
                break;
            }
        }
        else if(IsOperator(ch))
        {
            if(ch == '(')
            {
                cursor++;
                
                double value = ParseArithmeticExpression(&cursor, 0.0, PARSE_PHASE_STATUS_LEFT_OPERAND | PARSE_PHASE_STATUS_LEFT_PARENTHESIS, OPERATOR_PRIORITY_ADD, &isSuccessful);
                
                if(!isSuccessful || *cursor != ')')
                {
                    isSuccessful = false;
                    break;
                }
                
                if((status & PARSE_PHASE_STATUS_RIGHT_OPERAND) == 0)
                {
                    if(pMathFunc != NULL)
                    {
                        leftOperand = pMathFunc(value);
                        pMathFunc = NULL;
                    }
                    else
                        leftOperand = value;
                }
                else
                {
                    if(pMathFunc != NULL)
                    {
                        rightOperand = pMathFunc(value);
                        pMathFunc = NULL;
                    }
                    else
                        rightOperand = value;
                }

                status &= ~PARSE_PHASE_STATUS_LEFT_PARENTHESIS;
                
                status |= PARSE_PHASE_STATUS_NEED_OPERATOR;
            }
            else if(ch == ')')
            {
                *ppCursor = cursor;
                
                return (pOpFunc != NULL)? pOpFunc(leftOperand, rightOperand) : leftOperand;
            }
            else
            {
                if((status & PARSE_PHASE_STATUS_NEED_OPERATOR) == 0)
                {
                    if(ch == '-')
                    {
                        if(IsDigital(cursor[1]) || IsMathConstant(&cursor[1]) > 0)
                           status |= PARSE_PHASE_STATUS_HAS_NEG;
                        else
                        {
                            isSuccessful = false;
                            break;
                        }
                    }
                    else
                    {
                        isSuccessful = false;
                        break;
                    }
                }
                else
                {
                    var tmpFunc = opFuncTables[ch - '%'];
                    if(tmpFunc == NULL)
                    {
                        isSuccessful = false;
                        break;
                    }
                    var pry = OPERATOR_PRIORITY_ADD;
                    if(tmpFunc == ModOp || tmpFunc == MulOp || tmpFunc == DivOp)
                        pry = OPERATOR_PRIORITY_MUL;
                    else if(tmpFunc == pow)
                        pry = OPERATOR_PRIORITY_POW;
                    
                    if(pOpFunc == NULL)
                        pOpFunc = tmpFunc;
                    
                    if((status & PARSE_PHASE_STATUS_RIGHT_OPERAND) == 0)
                    {
                        status |= PARSE_PHASE_STATUS_RIGHT_OPERAND;
                    }
                    else
                    {
                        if(priority >= pry)
                        {
                            leftOperand = pOpFunc(leftOperand, rightOperand);
                            rightOperand = 0.0;
                            pOpFunc = tmpFunc;
                        }
                        else
                        {
                            if(pOpFunc == MinusOp)
                            {
                                pOpFunc = AddOp;
                                rightOperand = -rightOperand;
                            }
                            else if(pOpFunc == DivOp)
                            {
                                pOpFunc = MulOp;
                                rightOperand = 1.0 / rightOperand;
                            }
                            
                            var value = ParseArithmeticExpression(&cursor, rightOperand, PARSE_PHASE_STATUS_LEFT_OPERAND | PARSE_PHASE_STATUS_NEED_OPERATOR, pry, pStatus);

                            *ppCursor = cursor;
                            return pOpFunc(leftOperand, value);
                        }
                    }
                    priority = pry;
                }
                status &= ~PARSE_PHASE_STATUS_NEED_OPERATOR;
            }
            
            cursor++;
        }
        else
        {
            if(ch != '\0')
            {
                isSuccessful = false;
                break;
            }
        }
    }
    while(ch != '\0');
    
    if(!isSuccessful)
        pOpFunc = NULL;
    
    if(pStatus != NULL)
        *pStatus = isSuccessful;
    
    return (pOpFunc == NULL)? leftOperand : pOpFunc(leftOperand, rightOperand);
}

bool CalculateArithmeticExpression(char expr[], char result[static 32])
{
    if(expr[0] == '\0')
        return false;
    
    var length = (int)strlen(expr);
    
    for(var i = 0; i < length; i++)
    {
        var ch = expr[i];

        switch(ch)
        {
        case '[':
            expr[i] = '(';
            break;
        case ']':
            expr[i] = ')';
            break;
        case '$':
            expr[i] = '^';
            break;
        case 'A' ... 'Z':
            expr[i] += 0x20;
            break;
        }
    }
    
    bool ret = false;
    
    var value = ParseArithmeticExpression((const char**)&expr, 0.0, PARSE_PHASE_STATUS_LEFT_OPERAND, OPERATOR_PRIORITY_ADD, &ret);
    
    if(!ret)
        return ret;
    
    sprintf(result, "%.8f", value);
    
    length = (int)strlen(result);
    var dotIndex = -1;
    var hasE = false;
    for(var i = 0; i < length; i++)
    {
        if(result[i] == '.')
            dotIndex = i;
        else if(result[i] == 'e')
            hasE = true;
    }
    if(dotIndex >= 0 && !hasE)
    {
        var index = length;
        
        while(--index > 0)
        {
            if(result[index] != '0')
                break;
            
            result[index] = '\0';
        }
        if(result[dotIndex + 1] == '\0')
            result[dotIndex] = '\0';
    }
    
    return true;
}


int main(int argc, const char * argv[])
{
    if(argc < 2)
    {
        puts("No expression to calculate!");
        return 0;
    }
    
    var length = strlen(argv[1]);
    if(length == 0)
    {
        puts("No expression to calculate!");
        return 0;
    }

    if(length > MAX_ARGUMENT_LENGTH)
        length = MAX_ARGUMENT_LENGTH;

    char argBuffer[MAX_ARGUMENT_LENGTH + 1];
    
    strncpy(argBuffer, argv[1], length);
    
    char result[32];
    
    var state = CalculateArithmeticExpression(argBuffer, result);
    
    printf("The arithmetic expression to be calculated: %s\n", argBuffer);
    
    if(state)
        printf("The answer is: %s\n", result);
    else
        puts("Invalid expression!");
}

