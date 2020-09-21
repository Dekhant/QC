using System;
using System.Linq;

namespace TriangleCheck
{
    public class Program
    {
        static bool CheckMaxDouble(double a, double b, double c)
        {
            return a > double.MaxValue || b > double.MaxValue || c > double.MaxValue;
        }

        static bool CheckNonpositiveNumber(double a, double b, double c)
        {
            return a <= 0 || b <= 0 || c <= 0;
        }

        static bool CheckTriangleExist(double a, double b, double c)
        {
            return a + b > c && b + c > a && a + c > b;
        }

        static bool CheckEquilateralTriangle(double a, double b, double c)
        {
            return a == b && a == c && b == c;
        }

        static bool CheckIsoscelesaTriangle(double a, double b, double c)
        {
            return a == b || b == c || a == c;
        }

        static void GetTriangleType(double a, double b, double c)
        {
            if (CheckMaxDouble(a, b, c) || CheckNonpositiveNumber(a, b, c))
            {
                Console.WriteLine("неизвестная ошибка");
                return;
            }
            else if (!CheckTriangleExist(a, b, c))
            {
                Console.WriteLine("это не треугольник");
                return;
            }
            else if (CheckEquilateralTriangle(a, b, c))
            {
                Console.WriteLine("равносторонний");
                return;
            }
            else if (CheckIsoscelesaTriangle(a, b, c))
            {
                Console.WriteLine("равнобедренный");
                return;
            }
            Console.WriteLine("обычный");
        }

        public static void Main(string[] args)
        {
            if (args.Length != 3)
            {
                Console.WriteLine("неизвестная ошибка");
                return;
            }
            try
            {
                double a = double.Parse(args[0]);
                double b = double.Parse(args[1]);
                double c = double.Parse(args[2]);

                GetTriangleType(a, b, c);
            }
            catch
            {
                Console.WriteLine("неизвестная ошибка");
            }
        }
    }
}