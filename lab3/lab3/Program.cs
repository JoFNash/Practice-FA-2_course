using System;
using Cache;
using TestVar;

namespace lab3
{
    class Program
    {
        
        static void Main(string[] args)
        {
            TimeSpan lifeTime = new TimeSpan(0, 0, 5, 1, 0);
            Cache<Test> appCache = new Cache<Test>(lifeTime, 3);

            appCache.Save("KEY1", new Test(1));
            appCache.Save("KEY2", new Test(2));
            appCache.Save("KEY3", new Test(3));

            Console.WriteLine("KEY2: " + appCache.Get("KEY2").GetValue().ToString());

            try
            {
                appCache.Save("newKEY", new Test(100));
            }
            catch (ArgumentException ex)
            {
                Console.WriteLine(ex.Message);
            }

            try
            {
                appCache.Get("KEY1");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            try
            {
                Console.WriteLine(appCache.Get("KEY100").GetValue().ToString());
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }
    }
}
