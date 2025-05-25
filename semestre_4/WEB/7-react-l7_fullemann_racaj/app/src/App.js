import { BrowserRouter, Routes, Route } from "react-router-dom";
import HomePage from "./pages/HomePage";
import PlaylistPage from "./pages/PlaylistPage";
import Layout from "./components/Layout";
import { PlayerProvider } from "./context/PlayerContext";

function App() {
  return (
    <BrowserRouter>
      <PlayerProvider>
        <Layout>
          <Routes>
            <Route path="/" element={<HomePage />} />
            <Route path="/playlist/:id" element={<PlaylistPage />} />
          </Routes>
        </Layout>
      </PlayerProvider>
    </BrowserRouter>
  );
}

export default App;