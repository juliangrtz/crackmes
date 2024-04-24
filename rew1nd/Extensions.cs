namespace Rew1nd
{
    static class Extensions
    {
        public static string Rot47Decode(this string str)
        {
            return Rot47.rot47_it(str);
        }
    }
}
