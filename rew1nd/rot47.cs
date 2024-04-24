using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Rew1nd
{
    public class Rot47
    {

        public static IEnumerable<byte> ByteSequence(byte min, byte max)
        {
            while (min <= max)
            {
                yield return min++;
            }
        }

        public static byte[] JoinByteArrays(byte[] b1, byte[] b2)
        {
            List<byte> l1 = b1.ToList();
            List<byte> l2 = b2.ToList();
            List<byte> l3 = new List<byte>();
            l3.AddRange(l1);
            l3.AddRange(l2);
            return l3.ToArray();
        }

        public static string rot47_it(string data)
        {
            byte[] alphabet = ByteSequence(33, 126).ToArray();

            byte[] bytes = Encoding.ASCII.GetBytes(data);
            List<byte> output = new List<byte>();
            foreach (byte b in bytes)
            {
                byte n = b;
                if (n < 33 || n > 126)
                {
                    output.Add(n);
                }
                else
                {
                    int v = (n - 33) + 47;
                    if (v > 94)
                    {
                        v = v - 94;
                    }

                    if (v == 94)
                    {
                        v = 0;
                    }

                    output.Add(alphabet[Convert.ToByte(v)]);
                }

            }
            return Encoding.ASCII.GetString(output.ToArray());
        }
    }
}
