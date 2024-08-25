using System;
using System.Linq;
using System.Reflection;

namespace Layer3 {
    public class Layer3Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer4);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer4Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
