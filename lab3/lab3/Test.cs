using System;
using System.Collections.Generic;
using System.Text;

namespace TestVar
{
    class Test
    {
        public int number;
        public Test(int num)
        {
            number = num;
        }

        public int GetValue() 
        {
            return number;
        }
    }
}
