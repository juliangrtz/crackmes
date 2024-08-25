using System;
using System.Linq;
using System.Reflection;

namespace Layer4 {
    public class Layer4Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer5);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer5Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
