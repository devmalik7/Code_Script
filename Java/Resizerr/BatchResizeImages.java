import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class BatchResizeImages {

    public static void main(String[] args) {
        if (args.length != 4) {
            System.out.println("Usage: java BatchResizeImages <input_folder> <output_folder> <width> <height>");
            return;
        }

        String inputFolder = args[0];
        String outputFolder = args[1];
        int width = Integer.parseInt(args[2]);
        int height = Integer.parseInt(args[3]);

        File inputDir = new File(inputFolder);
        if (!inputDir.exists() || !inputDir.isDirectory()) {
            System.out.println("Input directory does not exist: " + inputFolder);
            return;
        }

        File outputDir = new File(outputFolder);
        if (!outputDir.exists()) {
            outputDir.mkdirs();
        }

        File[] files = inputDir.listFiles((_, name) -> name.toLowerCase().endsWith(".jpg") ||
                name.toLowerCase().endsWith(".jpeg") ||
                name.toLowerCase().endsWith(".jpg") ||
                name.toLowerCase().endsWith(".png"));

        if (files == null || files.length == 0) {
            System.out.println("No image files found in: " + inputFolder);
            return;
        }

        for (File file : files) {
            try {
                BufferedImage original = ImageIO.read(file);
                if (original == null) {
                    System.out.println("Skipping unreadable file: " + file.getName());
                    continue;
                }

                Image scaled = original.getScaledInstance(width, height, Image.SCALE_SMOOTH);
                BufferedImage resized = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);

                Graphics2D g2d = resized.createGraphics();
                g2d.drawImage(scaled, 0, 0, null);
                g2d.dispose();

                String format = file.getName().toLowerCase().endsWith(".png") ? "png" : "jpg";
                File outputFile = new File(outputDir, file.getName());
                ImageIO.write(resized, format, outputFile);

                System.out.println("✅ Resized: " + file.getName());
            } catch (Exception e) {
                System.out.println("❌ Error processing " + file.getName() + ": " + e.getMessage());
            }
        }

        System.out.println("\n🎉 All done! Resized images saved to: " + outputDir.getAbsolutePath());
    }
}
