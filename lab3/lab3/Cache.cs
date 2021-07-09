using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace Cache
{
    class Cache<T>
    {
        private TimeSpan time;
        private int size;
        private Dictionary<string, Tuple<T, DateTime>> dictionary;

        public Cache(TimeSpan time, int size) // время жизини записей
        {
            this.time = time;
            this.size = size;
            dictionary = new Dictionary<string, Tuple<T, DateTime>>();
        }

        public T Get(string key)
        {
            Tuple<T, DateTime>  value;

            DeleteElementsWithNoTime();
            if (!dictionary.TryGetValue(key, out value)) // почитать!
                throw new KeyNotFoundException();
            return value.Item1;
        }

        public void Save(string key, T data)
        {
            Tuple<T, DateTime> value;

            DeleteElementsWithNoTime();
            if (dictionary.TryGetValue(key, out value))
            {
                throw new ArgumentException();
            }
            else if (dictionary.Count == size)
            {
                TimeSpan difference = new TimeSpan(0);
                DateTime currentTime = DateTime.Now, creationTime;
                string oldestKeyValue = null;

                foreach (var i in dictionary)
                {
                    creationTime = i.Value.Item2; // узнаю тут время создания
                    if (currentTime - creationTime > difference)
                    {
                        difference = currentTime - creationTime;
                        oldestKeyValue = i.Key;
                    }
                }
                dictionary.Remove(oldestKeyValue);

                dictionary.Add(key, new Tuple<T, DateTime>(data, DateTime.Now));
            }
            else
            {
                dictionary.Add(key, new Tuple<T, DateTime>(data, DateTime.Now));
            }
        }

        private void DeleteElementsWithNoTime()
        {
            DateTime creationTime, currentTime = DateTime.Now;

            foreach (var i in dictionary)
            {
                creationTime = i.Value.Item2;
                if (currentTime - creationTime >= time)
                    dictionary.Remove(i.Key);
            }
        }
    }
}
