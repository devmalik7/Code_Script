import java.util.*;
import java.util.stream.Collectors;

public class TextSummarizer {

    // List of common stopwords
    private static final Set<String> STOPWORDS = Set.of(
            "a", "an", "the", "and", "or", "but", "is", "are", "was", "were",
            "in", "on", "at", "to", "for", "with", "of", "by", "that", "this"
    );

    public static void main(String[] args) {
        String text = """
                Java is a high-level, class-based, object-oriented programming language
                that is designed to have as few implementation dependencies as possible.
                It is a general-purpose programming language intended to let programmers
                write once, run anywhere (WORA), meaning that compiled Java code can run
                on all platforms that support Java without the need for recompilation.
                Java applications are typically compiled to bytecode that can run on any
                Java virtual machine (JVM) regardless of the underlying computer architecture.
                """;

        int summarySize = 2; // Number of sentences in summary
        String summary = summarizeText(text, summarySize);
        System.out.println("Summary:\n" + summary);
    }

    public static String summarizeText(String text, int numSentences) {
        // Split text into sentences
        String[] sentences = text.split("(?<=[.!?])\\s+");

        // Count word frequencies
        Map<String, Integer> wordFreq = new HashMap<>();
        for (String sentence : sentences) {
            String[] words = sentence.toLowerCase().split("\\W+");
            for (String word : words) {
                if (!STOPWORDS.contains(word) && word.length() > 1) {
                    wordFreq.put(word, wordFreq.getOrDefault(word, 0) + 1);
                }
            }
        }

        // Score sentences
        Map<String, Integer> sentenceScores = new HashMap<>();
        for (String sentence : sentences) {
            int score = 0;
            for (String word : sentence.toLowerCase().split("\\W+")) {
                score += wordFreq.getOrDefault(word, 0);
            }
            sentenceScores.put(sentence, score);
        }

        // Pick top sentences
        List<String> summarySentences = sentenceScores.entrySet().stream()
                .sorted(Map.Entry.<String, Integer>comparingByValue().reversed())
                .limit(numSentences)
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());

        return String.join(" ", summarySentences);
    }
}
