using Layer0.Properties;
using System.Linq;
using System.Reflection;

namespace Layer0
{
    public class Layer0Checker
    {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Resources.Layer1);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer1Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");

            return (bool)isValidFunction?.Invoke(null, new[] { username, licenseKey });
        }
    }
}
