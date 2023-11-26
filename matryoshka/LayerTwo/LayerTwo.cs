namespace Matryoshka
{
    public class LayerTwo
    {
        public static bool ValidateLicense(string name, string licenseKey)
        {
            return name.Equals("Julian") && licenseKey.Equals("XXXX");
        }
    }
}