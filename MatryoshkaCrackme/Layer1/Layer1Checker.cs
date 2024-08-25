using System;
using System.Linq;
using System.Reflection;

namespace Layer1 {
    public class Layer1Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer2);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer2Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
