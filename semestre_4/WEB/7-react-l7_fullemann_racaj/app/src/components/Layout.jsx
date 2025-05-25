import { Link, useLocation } from "react-router-dom";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faHome } from "@fortawesome/free-solid-svg-icons";
import AudioPlayer from "./AudioPlayer";
import QueueSidebar from "./QueueSidebar";

export default function Layout({ children }) {
  const location = useLocation();

  return (
    <div className="app">
      {/* Sidebar gauche */}
      <div className="sidebar">
        <div className="logo">
            <img src="/deezer-logo.svg" alt="Logo" className="logo-image" />
        </div>
        
        <nav>
          <Link 
            to="/" 
            className={`nav-item ${location.pathname === '/' ? 'active' : ''}`}
          >
            <FontAwesomeIcon icon={faHome} style={{ marginRight: '16px' }} />
            Accueil
          </Link>
        </nav>
      </div>

      {/* Contenu principal */}
      <div className="main-content">
        <div className="top-section">
          <div className="content-area">
            {children}
          </div>
          <QueueSidebar />
        </div>
        <AudioPlayer />
      </div>
    </div>
  );
}