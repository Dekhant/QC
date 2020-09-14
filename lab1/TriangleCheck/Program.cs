using System;
using System.Linq;

namespace TriangleCheck
{
    public class Program
    {
        public static void Main(string[] args)
        {
            if(args.Length != 3)
            {
                Console.WriteLine("неизвестная ошибка");
                return;
            }
            int i = 0;
            double[] mas = new double[3];
            foreach(var side in args)
            {
                bool success = double.TryParse(side, out mas[i]);
                if(!success)
                {
                    Console.WriteLine("неизвестная ошибка");
                    return;
                }
                i++;
            }
            double perimeter = mas.Sum();
            foreach(var side in mas)
            {
                if((perimeter - side) < side)
                {
                    Console.WriteLine("это не треугольник");
                    return;
                }
            }
            if(perimeter / 3 == mas[0])
            {
                Console.WriteLine("равносторонний");
                return;
            }
            if(mas[0] == mas[1] || mas[0] == mas[2] || mas[1] == mas[2])
            {
                Console.WriteLine("равнобедренный");
                return;
            }
            Console.WriteLine("обычный");
        }
    }
}