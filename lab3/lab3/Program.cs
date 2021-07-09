using System;
using Cache;
using TestVar;

namespace lab3
{
    class Program
    {
        
        static void Main(string[] args)
        {
            TimeSpan lifeTime = new TimeSpan(1, 1, 1, 1, 1);
            Cache<Test> cache = new Cache<Test>(lifeTime, 3);

            cache.Save("KEY1", new Test(1));
            cache.Save("KEY2", new Test(2));
            cache.Save("KEY3", new Test(3));

            Console.WriteLine("KEY2: " + cache.Get("KEY2").GetValue().ToString());

            try
            {
                cache.Save("newKEY", new Test(100));
            }
            catch (ArgumentException ex)
            {
                Console.WriteLine(ex.Message);
            }

            try
            {
                cache.Get("KEY1");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            try
            {
                Console.WriteLine(cache.Get("KEY100").GetValue().ToString());
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }
    }
}
